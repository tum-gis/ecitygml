use crate::color::feature_type_color;
use crate::mesh::{
    best_placement_per_owner, placement_instance_transform, prototype_to_cpu_mesh,
    triangulated_surface_to_cpu_mesh,
};
use bvh::aabb::{Aabb, Bounded};
use bvh::bounding_hierarchy::BHShape;
use bvh::bvh::Bvh;
use bvh::ray::Ray;
use ecitygml_core::model::common::{FeatureType, HasFeatureType};
use ecitygml_core::model::core::AsAbstractFeature;
use ecitygml_core::model::core::refs::AbstractCityObjectKindRef;
use ecitygml_core::store::CityModelGraphicsStore;
use ecitygml_core::store::ImplicitGeometryStore;
use egml::model::base::Id;
use egml::model::geometry::Envelope;
use nalgebra::Point3;
use std::collections::{HashMap, HashSet};
use std::sync::Arc;
use three_d::{
    AmbientLight, Camera, ClearState, Context, CpuMaterial, CpuMesh, DepthTest, DirectionalLight,
    Gm, Indices, InnerSpace, InstancedMesh, Instances, Mat4, Mesh, PhysicalMaterial, PhysicalPoint,
    Positions, RenderStates, Srgba, Vec3, WriteMask,
};

/// Positions, normals and indices of the meshes merged into one batch.
type MeshBuffers = (Vec<Vec3>, Vec<Vec3>, Vec<u32>);

/// Clear color used for the interactive viewport. Screenshot export uses its own
/// (white) background instead — see `screenshot::BACKGROUND` — so the two are
/// deliberately kept independent rather than sharing one constant.
pub const VIEWPORT_BACKGROUND: ClearState =
    ClearState::color_and_depth(243.0 / 255.0, 244.0 / 255.0, 246.0 / 255.0, 1.0, 1.0);

/// Vertical field of view the camera is constructed with in `main.rs`. `fit_camera` needs this
/// to compute a distance that frames the whole model, so it's shared rather than duplicated.
pub const CAMERA_FOV_Y_DEGREES: f32 = 45.0;

pub struct SceneEntry {
    pub id: Id,
    pub feature_type: FeatureType,
    bounds: Option<Aabb<f32, 3>>,
}

struct BoundedEntry {
    aabb: Aabb<f32, 3>,
    entry_index: usize,
    node_index: usize,
}

impl Bounded<f32, 3> for BoundedEntry {
    fn aabb(&self) -> Aabb<f32, 3> {
        self.aabb
    }
}

impl BHShape<f32, 3> for BoundedEntry {
    fn set_bh_node_index(&mut self, i: usize) {
        self.node_index = i;
    }
    fn bh_node_index(&self) -> usize {
        self.node_index
    }
}

pub struct Scene {
    pub entries: Vec<SceneEntry>,
    batches: Vec<(FeatureType, Gm<Mesh, PhysicalMaterial>)>,
    /// One GPU-instanced draw per (prototype geometry, feature type) pair — repeated implicit
    /// geometries (streetlights, standard trees, ...) sharing the same template render as a
    /// single instanced draw call instead of being cloned and merged per occurrence. Split by
    /// feature type (not just by prototype) so per-type visibility toggling in the sidebar still
    /// works even in the rare case where the same prototype is used by more than one type.
    instanced: Vec<(FeatureType, Gm<InstancedMesh, PhysicalMaterial>)>,
    /// Actual mesh of the selected object, shown when the camera is idle.
    selected_overlay: Option<Gm<Mesh, PhysicalMaterial>>,
    pub ambient: AmbientLight,
    pub sun: DirectionalLight,
    context: Context,
    center: Point3<f64>,
    graphics: Arc<CityModelGraphicsStore>,
    bvh: Bvh<f32, 3>,
    bvh_shapes: Vec<BoundedEntry>,
}

impl Scene {
    pub fn from_store(context: &Context, graphics: Arc<CityModelGraphicsStore>) -> Self {
        let city_objects: Vec<AbstractCityObjectKindRef<'_>> =
            graphics.city_model_arena.iter_city_objects().collect();

        let center = compute_center(&city_objects);

        let mut cpu_buckets: HashMap<FeatureType, MeshBuffers> = HashMap::new();
        let mut entries: Vec<SceneEntry> = Vec::new();

        for city_object in &city_objects {
            let feature_type = city_object.feature_type();
            entries.push(SceneEntry {
                id: city_object.feature_id().clone(),
                feature_type,
                bounds: build_bounds(city_object, &center),
            });

            // Implicit geometries are drawn separately as GPU instances below, not merged here.
            if let Some(triangulation) =
                CityModelGraphicsStore::best_triangulated_surface(*city_object)
            {
                for skipped in triangulation.skipped() {
                    tracing::warn!(
                        "geometry member skipped while triangulating {}: {skipped}",
                        city_object.feature_id().as_str()
                    );
                }
                if let Some(cpu_mesh) =
                    triangulated_surface_to_cpu_mesh(triangulation.surface(), &center)
                {
                    let bucket = cpu_buckets.entry(feature_type).or_default();
                    merge_into(bucket, &cpu_mesh);
                }
            }
        }

        let batches: Vec<(FeatureType, Gm<Mesh, PhysicalMaterial>)> = cpu_buckets
            .into_iter()
            .map(|(ft, (positions, normals, indices))| {
                let cpu_mesh = CpuMesh {
                    positions: Positions::F32(positions),
                    normals: Some(normals),
                    indices: Indices::U32(indices),
                    ..Default::default()
                };
                let color = feature_type_color(ft);
                let gm = Gm::new(
                    Mesh::new(context, &cpu_mesh),
                    PhysicalMaterial::new_opaque(
                        context,
                        &CpuMaterial {
                            albedo: color,
                            ..Default::default()
                        },
                    ),
                );
                (ft, gm)
            })
            .collect();

        let instanced = build_instanced_meshes(
            context,
            &city_objects,
            &graphics.implicit_geometry_store,
            &center,
        );

        let mut bvh_shapes: Vec<BoundedEntry> = entries
            .iter()
            .enumerate()
            .filter_map(|(i, e)| {
                e.bounds.map(|aabb| BoundedEntry {
                    aabb,
                    entry_index: i,
                    node_index: 0,
                })
            })
            .collect();
        let bvh = Bvh::build(&mut bvh_shapes);

        let ambient = AmbientLight::new(context, 0.55, Srgba::WHITE);
        let sun = DirectionalLight::new(context, 2.1, Srgba::WHITE, Vec3::new(-1.0, -2.0, -1.5));

        Self {
            entries,
            batches,
            instanced,
            selected_overlay: None,
            ambient,
            sun,
            context: context.clone(),
            center,
            graphics,
            bvh,
            bvh_shapes,
        }
    }

    pub fn render(
        &self,
        target: &three_d::RenderTarget,
        camera: &Camera,
        hidden: &HashSet<FeatureType>,
        clear: ClearState,
    ) {
        let lights: &[&dyn three_d::Light] = &[&self.ambient, &self.sun];
        let visible: Vec<&Gm<Mesh, PhysicalMaterial>> = self
            .batches
            .iter()
            .filter(|(ft, _)| !hidden.contains(ft))
            .map(|(_, gm)| gm)
            .collect();
        let visible_instanced: Vec<&Gm<InstancedMesh, PhysicalMaterial>> = self
            .instanced
            .iter()
            .filter(|(ft, _)| !hidden.contains(ft))
            .map(|(_, gm)| gm)
            .collect();

        target.clear(clear).render(camera, visible, lights);
        target.render(camera, visible_instanced, lights);

        if let Some(overlay) = &self.selected_overlay {
            target.render(camera, [overlay], lights);
        }
    }

    /// Called when the user starts dragging — hides the overlay for zero cost during motion.
    pub fn on_camera_moving(&mut self) {
        self.selected_overlay = None;
    }

    /// Called when the camera becomes idle — rebuilds the overlay with the actual object mesh.
    pub fn on_camera_idle(&mut self, selected_id: Option<&Id>) {
        self.selected_overlay = selected_id.and_then(|id| self.build_highlight(id));
    }

    /// Called on selection change (only when camera is idle).
    pub fn set_selected(&mut self, id: Option<&Id>) {
        self.selected_overlay = id.and_then(|id| self.build_highlight(id));
    }

    pub fn pick_at(
        &self,
        camera: &Camera,
        pixel: PhysicalPoint,
        hidden: &HashSet<FeatureType>,
    ) -> Option<Id> {
        let (_, idx) = self.cast_ray(camera, pixel, hidden)?;
        self.entries.get(idx).map(|e| e.id.clone())
    }

    /// Returns the world-space hit point of the closest AABB under `pixel`.
    pub fn pick_world_point(
        &self,
        camera: &Camera,
        pixel: PhysicalPoint,
        hidden: &HashSet<FeatureType>,
    ) -> Option<Vec3> {
        let origin = camera.position_at_pixel(pixel);
        let dir = camera.view_direction_at_pixel(pixel);
        let (t, _) = self.cast_ray(camera, pixel, hidden)?;
        Some(origin + dir * t)
    }

    fn cast_ray(
        &self,
        camera: &Camera,
        pixel: PhysicalPoint,
        hidden: &HashSet<FeatureType>,
    ) -> Option<(f32, usize)> {
        let origin = camera.position_at_pixel(pixel);
        let dir = camera.view_direction_at_pixel(pixel);

        let ray = Ray::new(
            [origin.x, origin.y, origin.z].into(),
            [dir.x, dir.y, dir.z].into(),
        );
        let inv = [1.0 / dir.x, 1.0 / dir.y, 1.0 / dir.z];
        let o = [origin.x, origin.y, origin.z];

        self.bvh
            .traverse(&ray, &self.bvh_shapes)
            .into_iter()
            .filter_map(|shape| {
                let entry = self.entries.get(shape.entry_index)?;
                if hidden.contains(&entry.feature_type) {
                    return None;
                }
                let a = &shape.aabb;
                let t = aabb_entry_t(
                    &o,
                    &inv,
                    [a.min[0], a.min[1], a.min[2]],
                    [a.max[0], a.max[1], a.max[2]],
                )?;
                Some((t, shape.entry_index))
            })
            .min_by(|a, b| a.0.partial_cmp(&b.0).unwrap_or(std::cmp::Ordering::Equal))
    }

    /// Frames the whole model, not just a fixed-size neighborhood of the origin: distance is
    /// derived from the actual bounding box of every entry so both small fixtures and
    /// city-scale datasets end up fully visible after load or on "recenter".
    pub fn fit_camera(&self, camera: &mut Camera) {
        let overall = self
            .entries
            .iter()
            .filter_map(|e| e.bounds)
            .fold(Aabb::empty(), |acc, b| acc.join(&b));
        if overall.is_empty() {
            return;
        }

        let center = overall.center();
        let size = overall.size();
        let radius = (size.x * size.x + size.y * size.y + size.z * size.z).sqrt() * 0.5;
        let radius = radius.max(1.0);

        let half_fov_y = (CAMERA_FOV_Y_DEGREES / 2.0).to_radians();
        let half_fov_x = (half_fov_y.tan() * camera.viewport().aspect()).atan();
        let half_fov = half_fov_y.min(half_fov_x);
        // 1.15x padding so the model doesn't touch the viewport edges exactly.
        let distance = radius / half_fov.tan() * 1.0;

        // Camera sits south of and above the target, at a 45° tilt, so the initial view looks
        // north — the CRS convention assumed here is X = easting, Y = northing, Z = height.
        let direction = Vec3::new(0.0, -1.0, 1.0).normalize();
        let target = Vec3::new(center.x, center.y, center.z);
        camera.set_view(
            target + direction * distance,
            target,
            Vec3::new(0.0, 0.0, 1.0),
        );
    }

    fn build_highlight(&self, id: &Id) -> Option<Gm<Mesh, PhysicalMaterial>> {
        let city_object = self.graphics.city_model_arena.get_city_object_by_id(id)?;
        let triangulation = CityModelGraphicsStore::best_triangulated_surface(city_object)?;
        for skipped in triangulation.skipped() {
            tracing::warn!(
                "geometry member skipped while triangulating {}: {skipped}",
                id.as_str()
            );
        }
        let cpu_mesh = triangulated_surface_to_cpu_mesh(triangulation.surface(), &self.center)?;
        let highlight_color = Srgba::new(255, 220, 50, 255);
        let mut material = PhysicalMaterial::new_opaque(
            &self.context,
            &CpuMaterial {
                albedo: highlight_color,
                ..Default::default()
            },
        );
        // Pass depth test at equal depth (same geometry as the batch), don't re-write depth.
        material.render_states = RenderStates {
            depth_test: DepthTest::LessOrEqual,
            write_mask: WriteMask {
                depth: false,
                ..WriteMask::COLOR
            },
            ..Default::default()
        };
        Some(Gm::new(Mesh::new(&self.context, &cpu_mesh), material))
    }
}

/// Builds one GPU-instanced draw per (prototype geometry, feature type) pair from the
/// [`ImplicitGeometryStore`]: every occurrence sharing a prototype (e.g. hundreds of
/// identical streetlights) becomes a single instanced draw call instead of being cloned,
/// triangulated, and merged individually. Split by feature type — not just by prototype — so
/// the sidebar's per-type visibility toggle still works even if the same prototype is
/// (unusually) shared across types.
fn build_instanced_meshes(
    context: &Context,
    city_objects: &[AbstractCityObjectKindRef<'_>],
    implicit_geometry_resolver: &ImplicitGeometryStore,
    center: &Point3<f64>,
) -> Vec<(FeatureType, Gm<InstancedMesh, PhysicalMaterial>)> {
    let id_to_class: HashMap<&Id, FeatureType> = city_objects
        .iter()
        .map(|x| (x.feature_id(), x.feature_type()))
        .collect();

    let mut instanced = Vec::new();

    for (_, geometry, placements) in implicit_geometry_resolver.prototypes_with_placements() {
        let best = best_placement_per_owner(&placements);
        let Some(cpu_mesh) = prototype_to_cpu_mesh(geometry) else {
            continue;
        };

        let mut by_type: HashMap<FeatureType, Vec<Mat4>> = HashMap::new();
        for (feature_id, placement) in &best {
            let Some(&class) = id_to_class.get(feature_id) else {
                continue;
            };
            by_type
                .entry(class)
                .or_default()
                .push(placement_instance_transform(placement, center));
        }

        for (feature_type, transformations) in by_type {
            instanced.push(instanced_gm(
                context,
                &cpu_mesh,
                transformations,
                feature_type,
            ));
        }
    }

    instanced
}

fn instanced_gm(
    context: &Context,
    cpu_mesh: &CpuMesh,
    transformations: Vec<Mat4>,
    feature_type: FeatureType,
) -> (FeatureType, Gm<InstancedMesh, PhysicalMaterial>) {
    let instances = Instances {
        transformations,
        texture_transformations: None,
        colors: None,
    };
    let gm = Gm::new(
        InstancedMesh::new(context, &instances, cpu_mesh),
        PhysicalMaterial::new_opaque(
            context,
            &CpuMaterial {
                albedo: feature_type_color(feature_type),
                ..Default::default()
            },
        ),
    );
    (feature_type, gm)
}

fn merge_into(bucket: &mut MeshBuffers, src: &CpuMesh) {
    let (positions, normals, indices) = bucket;
    let base = positions.len() as u32;

    let src_positions = match &src.positions {
        Positions::F32(v) => v,
        _ => return,
    };
    positions.extend_from_slice(src_positions);

    if let Some(src_normals) = &src.normals {
        normals.extend_from_slice(src_normals);
    } else {
        normals.extend(std::iter::repeat_n(
            Vec3::new(0.0, 0.0, 1.0),
            src_positions.len(),
        ));
    }

    match &src.indices {
        Indices::U32(idx) => indices.extend(idx.iter().map(|i| i + base)),
        Indices::U16(idx) => indices.extend(idx.iter().map(|i| *i as u32 + base)),
        Indices::U8(idx) => indices.extend(idx.iter().map(|i| *i as u32 + base)),
        Indices::None => indices.extend(base..base + src_positions.len() as u32),
    }
}

fn build_bounds(
    city_object: &AbstractCityObjectKindRef<'_>,
    center: &Point3<f64>,
) -> Option<Aabb<f32, 3>> {
    let env = egml::model::feature::AsAbstractFeature::bounded_by(city_object)
        .and_then(|x| x.envelope())?;
    Some(Aabb::with_bounds(
        [
            (env.lower_corner().x() - center.x) as f32,
            (env.lower_corner().y() - center.y) as f32,
            (env.lower_corner().z() - center.z) as f32,
        ]
        .into(),
        [
            (env.upper_corner().x() - center.x) as f32,
            (env.upper_corner().y() - center.y) as f32,
            (env.upper_corner().z() - center.z) as f32,
        ]
        .into(),
    ))
}

fn aabb_entry_t(o: &[f32; 3], inv: &[f32; 3], min: [f32; 3], max: [f32; 3]) -> Option<f32> {
    let mut tmin = f32::NEG_INFINITY;
    let mut tmax = f32::INFINITY;
    for i in 0..3 {
        let t1 = (min[i] - o[i]) * inv[i];
        let t2 = (max[i] - o[i]) * inv[i];
        tmin = tmin.max(t1.min(t2));
        tmax = tmax.min(t1.max(t2));
    }
    if tmax >= 0.0 && tmin <= tmax {
        Some(tmin.max(0.0))
    } else {
        None
    }
}

fn compute_center(city_objects: &[AbstractCityObjectKindRef<'_>]) -> Point3<f64> {
    let envelopes: Vec<&Envelope> = city_objects
        .iter()
        .filter_map(egml::model::feature::AsAbstractFeature::bounded_by)
        .filter_map(|x| x.envelope())
        .collect();
    if envelopes.is_empty() {
        return Point3::origin();
    }
    let sum = envelopes.iter().fold([0.0f64; 3], |acc, env| {
        let c = env.center();
        [acc[0] + c.x(), acc[1] + c.y(), acc[2] + c.z()]
    });
    let n = envelopes.len() as f64;
    Point3::new(sum[0] / n, sum[1] / n, sum[2] / n)
}

#[expect(dead_code, reason = "not used yet")]
fn brighten(c: Srgba) -> Srgba {
    Srgba::new(
        (c.r as u16 + 80).min(255) as u8,
        (c.g as u16 + 80).min(255) as u8,
        (c.b as u16 + 80).min(255) as u8,
        c.a,
    )
}
