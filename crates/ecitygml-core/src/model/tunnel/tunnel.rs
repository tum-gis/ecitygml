use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::tunnel_part_property::TunnelPartProperty;
use crate::model::tunnel::{AbstractTunnel, AsAbstractTunnel, AsAbstractTunnelMut};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct Tunnel {
    pub(crate) abstract_tunnel: AbstractTunnel,
    tunnel_parts: Vec<TunnelPartProperty>,
}

impl Tunnel {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_tunnel(AbstractTunnel::new(id))
    }

    pub fn from_abstract_tunnel(abstract_tunnel: AbstractTunnel) -> Self {
        Self {
            abstract_tunnel,
            tunnel_parts: Vec::new(),
        }
    }

    pub fn tunnel_parts(&self) -> &[TunnelPartProperty] {
        &self.tunnel_parts
    }

    pub fn tunnel_parts_mut(&mut self) -> &mut [TunnelPartProperty] {
        &mut self.tunnel_parts
    }

    pub fn set_tunnel_parts(&mut self, tunnel_parts: Vec<TunnelPartProperty>) {
        self.tunnel_parts = tunnel_parts;
    }

    pub fn push_tunnel_part(&mut self, tunnel_part: TunnelPartProperty) {
        self.tunnel_parts.push(tunnel_part);
    }

    pub fn extend_tunnel_parts(
        &mut self,
        tunnel_parts: impl IntoIterator<Item = TunnelPartProperty>,
    ) {
        self.tunnel_parts.extend(tunnel_parts);
    }
}

impl AsAbstractTunnel for Tunnel {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        &self.abstract_tunnel
    }
}

impl AsAbstractTunnelMut for Tunnel {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel {
        &mut self.abstract_tunnel
    }
}

crate::impl_abstract_tunnel_traits!(Tunnel);
crate::impl_abstract_tunnel_mut_traits!(Tunnel);
crate::impl_has_feature_type!(Tunnel, Tunnel);

impl IterFeatures for Tunnel {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into())
                .chain(self.abstract_tunnel.iter_features())
                .chain(
                    self.tunnel_parts
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for Tunnel {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_tunnel.for_each_feature_mut(f);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for Tunnel {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_tunnel.compute_envelope()
    }
}

impl ApplyTransform for Tunnel {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_tunnel.apply_transform(m);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_tunnel.apply_isometry(isometry);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_tunnel.apply_translation(vector);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_tunnel.apply_rotation(rotation);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_tunnel.apply_scale(scale);

        for prop in &mut self.tunnel_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};
    use crate::model::tunnel::{
        AsAbstractTunnelMut, HollowSpace, HollowSpaceProperty, TunnelFurniture,
        TunnelFurnitureProperty, TunnelPart, TunnelPartProperty,
    };

    fn tunnel_with_part() -> Tunnel {
        let mut tunnel = Tunnel::new(Id::try_from("tunnel").expect("valid id"));
        tunnel.push_tunnel_part(TunnelPartProperty::from_object(TunnelPart::new(
            Id::try_from("tunnel_part").expect("valid id"),
        )));
        tunnel
    }

    #[test]
    fn test_iter_features_yields_tunnel_and_its_parts() {
        let feature_types: Vec<FeatureType> = tunnel_with_part()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(
            feature_types,
            vec![FeatureType::Tunnel, FeatureType::TunnelPart]
        );
    }

    #[test]
    fn test_for_each_feature_mut_visits_tunnel_and_its_parts() {
        let mut feature_types = Vec::new();
        tunnel_with_part().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(
            feature_types,
            vec![FeatureType::Tunnel, FeatureType::TunnelPart]
        );
    }

    fn tunnel_with_hollow_space() -> Tunnel {
        let mut tunnel = Tunnel::new(Id::try_from("tunnel").expect("valid id"));
        tunnel.push_hollow_space(HollowSpaceProperty::from_object(HollowSpace::new(
            Id::try_from("hollow_space").expect("valid id"),
        )));
        tunnel
    }

    #[test]
    fn test_iter_features_yields_tunnel_and_its_hollow_spaces() {
        let feature_types: Vec<FeatureType> = tunnel_with_hollow_space()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(
            feature_types,
            vec![FeatureType::Tunnel, FeatureType::HollowSpace]
        );
    }

    #[test]
    fn test_for_each_feature_mut_visits_tunnel_and_its_hollow_spaces() {
        let mut feature_types = Vec::new();
        tunnel_with_hollow_space()
            .for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(
            feature_types,
            vec![FeatureType::Tunnel, FeatureType::HollowSpace]
        );
    }

    fn tunnel_with_furniture_on_tunnel_and_in_hollow_space() -> Tunnel {
        let mut hollow_space = HollowSpace::new(Id::try_from("hollow_space").expect("valid id"));
        hollow_space.push_tunnel_furniture(TunnelFurnitureProperty::from_object(
            TunnelFurniture::new(Id::try_from("hollow_space_furniture").expect("valid id")),
        ));

        let mut tunnel = Tunnel::new(Id::try_from("tunnel").expect("valid id"));
        tunnel.push_hollow_space(HollowSpaceProperty::from_object(hollow_space));
        tunnel.push_tunnel_furniture(TunnelFurnitureProperty::from_object(TunnelFurniture::new(
            Id::try_from("tunnel_furniture").expect("valid id"),
        )));
        tunnel
    }

    #[test]
    fn test_iter_features_yields_furniture_on_tunnel_and_in_hollow_spaces() {
        let feature_types: Vec<FeatureType> = tunnel_with_furniture_on_tunnel_and_in_hollow_space()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(
            feature_types,
            vec![
                FeatureType::Tunnel,
                FeatureType::HollowSpace,
                FeatureType::TunnelFurniture,
                FeatureType::TunnelFurniture
            ]
        );
    }

    #[test]
    fn test_for_each_feature_mut_visits_furniture_on_tunnel_and_in_hollow_spaces() {
        let mut feature_types = Vec::new();
        tunnel_with_furniture_on_tunnel_and_in_hollow_space()
            .for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(
            feature_types,
            vec![
                FeatureType::Tunnel,
                FeatureType::HollowSpace,
                FeatureType::TunnelFurniture,
                FeatureType::TunnelFurniture
            ]
        );
    }
}
