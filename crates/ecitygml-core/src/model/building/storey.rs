use crate::impl_abstract_building_subdivision_mut_traits;
use crate::impl_abstract_building_subdivision_traits;
use crate::model::building::{
    AbstractBuildingSubdivision, AsAbstractBuildingSubdivision, AsAbstractBuildingSubdivisionMut,
};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct Storey {
    pub(crate) abstract_building_subdivision: AbstractBuildingSubdivision,
}

impl Storey {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_building_subdivision(AbstractBuildingSubdivision::new(id))
    }

    pub fn from_abstract_building_subdivision(
        abstract_building_subdivision: AbstractBuildingSubdivision,
    ) -> Self {
        Self {
            abstract_building_subdivision,
        }
    }
}

impl AsAbstractBuildingSubdivision for Storey {
    fn abstract_building_subdivision(&self) -> &AbstractBuildingSubdivision {
        &self.abstract_building_subdivision
    }
}

impl AsAbstractBuildingSubdivisionMut for Storey {
    fn abstract_building_subdivision_mut(&mut self) -> &mut AbstractBuildingSubdivision {
        &mut self.abstract_building_subdivision
    }
}

impl_abstract_building_subdivision_traits!(Storey);
impl_abstract_building_subdivision_mut_traits!(Storey);
crate::impl_has_feature_type!(Storey, Storey);

impl IterFeatures for Storey {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into()).chain(self.abstract_building_subdivision.iter_features()),
        )
    }
}

impl ForEachFeatureMut for Storey {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_building_subdivision.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for Storey {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_building_subdivision.compute_envelope()
    }
}

impl ApplyTransform for Storey {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_building_subdivision.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_building_subdivision.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_building_subdivision.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_building_subdivision.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_building_subdivision.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::building::{
        BuildingConstructiveElement, BuildingConstructiveElementProperty, BuildingFurniture,
        BuildingFurnitureProperty, BuildingInstallation, BuildingInstallationProperty,
        BuildingRoom, BuildingRoomProperty,
    };
    use crate::model::common::{FeatureType, HasFeatureType};
    use crate::model::construction::{Elevation, ElevationValue};
    use egml::model::basic_types::Code;
    use egml::model::feature::{AsAbstractFeature, AsAbstractFeatureMut, BoundingShape};
    use egml::model::geometry::DirectPosition;

    fn id(value: &str) -> Id {
        Id::try_from(value).expect("valid id")
    }

    fn envelope(offset: f64) -> Option<BoundingShape> {
        let corner = |value: f64| DirectPosition::new(value, value, value).expect("finite");
        let envelope = Envelope::new(corner(offset), corner(offset + 1.0)).expect("valid envelope");
        Some(BoundingShape::new(envelope))
    }

    /// A storey with one feature of each nested kind, each with its own envelope.
    fn storey_with_nested_features() -> Storey {
        let mut element = BuildingConstructiveElement::new(id("element"));
        element.set_bounded_by(envelope(1.0));
        let mut furniture = BuildingFurniture::new(id("furniture"));
        furniture.set_bounded_by(envelope(2.0));
        let mut installation = BuildingInstallation::new(id("installation"));
        installation.set_bounded_by(envelope(3.0));
        let mut room = BuildingRoom::new(id("room"));
        room.set_bounded_by(envelope(4.0));

        let mut storey = Storey::new(id("storey"));
        storey.set_bounded_by(envelope(0.0));
        storey.push_building_constructive_element(
            BuildingConstructiveElementProperty::from_object(element),
        );
        storey.push_building_furniture(BuildingFurnitureProperty::from_object(furniture));
        storey.push_building_installation(BuildingInstallationProperty::from_object(installation));
        storey.push_building_room(BuildingRoomProperty::from_object(room));
        storey
    }

    const NESTED_IN_SCHEMA_ORDER: [FeatureType; 5] = [
        FeatureType::Storey,
        FeatureType::BuildingConstructiveElement,
        FeatureType::BuildingFurniture,
        FeatureType::BuildingInstallation,
        FeatureType::BuildingRoom,
    ];

    #[test]
    fn test_iter_features_yields_nested_features() {
        let feature_types: Vec<FeatureType> = storey_with_nested_features()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(feature_types, NESTED_IN_SCHEMA_ORDER);
    }

    #[test]
    fn test_for_each_feature_mut_visits_nested_features() {
        let mut feature_types = Vec::new();
        storey_with_nested_features()
            .for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(feature_types, NESTED_IN_SCHEMA_ORDER);
    }

    #[test]
    fn test_apply_translation_moves_nested_features_once() {
        let mut storey = storey_with_nested_features();
        storey.apply_translation(Vector3::new(10.0, 20.0, 30.0));

        let lower_corners: Vec<[f64; 3]> = storey
            .iter_features()
            .filter_map(|feature| {
                let lower = *feature.bounded_by()?.envelope()?.lower_corner();
                Some([lower.x(), lower.y(), lower.z()])
            })
            .collect();
        let moved = |offset: f64| [offset + 10.0, offset + 20.0, offset + 30.0];
        assert_eq!(
            lower_corners,
            [moved(0.0), moved(1.0), moved(2.0), moved(3.0), moved(4.0)]
        );
    }

    #[test]
    fn test_elevations_and_sort_key_accessors() {
        let elevation = |value: f64| {
            Elevation::new(
                Code::new("lowestGroundPoint").into(),
                ElevationValue::new(vec![value]).expect("should work"),
            )
        };
        let mut storey = Storey::new(id("storey"));
        assert!(storey.elevations().is_empty());
        assert_eq!(storey.sort_key(), None);

        storey.push_elevation(elevation(0.0));
        storey.extend_elevations([elevation(2.7)]);
        assert_eq!(storey.elevations(), &[elevation(0.0), elevation(2.7)]);
        storey.set_elevations(vec![elevation(5.4)]);
        assert_eq!(storey.elevations(), &[elevation(5.4)]);

        storey.set_sort_key(2.0);
        assert_eq!(storey.sort_key(), Some(2.0));
        storey.clear_sort_key();
        assert_eq!(storey.sort_key(), None);
    }
}
