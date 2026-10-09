use crate::model::bridge::bridge_part_property::BridgePartProperty;
use crate::model::bridge::{AbstractBridge, AsAbstractBridge, AsAbstractBridgeMut};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct Bridge {
    pub(crate) abstract_bridge: AbstractBridge,
    bridge_parts: Vec<BridgePartProperty>,
}

impl Bridge {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_bridge(AbstractBridge::new(id))
    }

    pub fn from_abstract_bridge(abstract_bridge: AbstractBridge) -> Self {
        Self {
            abstract_bridge,
            bridge_parts: Vec::new(),
        }
    }

    pub fn bridge_parts(&self) -> &[BridgePartProperty] {
        &self.bridge_parts
    }

    pub fn bridge_parts_mut(&mut self) -> &mut [BridgePartProperty] {
        &mut self.bridge_parts
    }

    pub fn set_bridge_parts(&mut self, bridge_parts: Vec<BridgePartProperty>) {
        self.bridge_parts = bridge_parts;
    }

    pub fn push_bridge_part(&mut self, bridge_part: BridgePartProperty) {
        self.bridge_parts.push(bridge_part);
    }

    pub fn extend_bridge_parts(
        &mut self,
        bridge_parts: impl IntoIterator<Item = BridgePartProperty>,
    ) {
        self.bridge_parts.extend(bridge_parts);
    }
}

impl AsAbstractBridge for Bridge {
    fn abstract_bridge(&self) -> &AbstractBridge {
        &self.abstract_bridge
    }
}

impl AsAbstractBridgeMut for Bridge {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge {
        &mut self.abstract_bridge
    }
}

crate::impl_abstract_bridge_traits!(Bridge);
crate::impl_abstract_bridge_mut_traits!(Bridge);
crate::impl_has_feature_type!(Bridge, Bridge);

impl IterFeatures for Bridge {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(
            std::iter::once(self.into())
                .chain(self.abstract_bridge.iter_features())
                .chain(
                    self.bridge_parts
                        .iter()
                        .filter_map(|x| x.object())
                        .flat_map(|x| x.iter_features()),
                ),
        )
    }
}

impl ForEachFeatureMut for Bridge {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_bridge.for_each_feature_mut(f);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.for_each_feature_mut(f);
            }
        }
    }
}

impl ComputeEnvelope for Bridge {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_bridge.compute_envelope()
    }
}

impl ApplyTransform for Bridge {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_bridge.apply_transform(m);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_transform(m);
            }
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_bridge.apply_isometry(isometry);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_isometry(isometry);
            }
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_bridge.apply_translation(vector);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_translation(vector);
            }
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_bridge.apply_rotation(rotation);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_rotation(rotation);
            }
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_bridge.apply_scale(scale);

        for prop in &mut self.bridge_parts {
            if let Some(x) = prop.object_mut() {
                x.apply_scale(scale);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::bridge::{BridgePart, BridgePartProperty};
    use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};

    fn bridge_with_part() -> Bridge {
        let mut bridge = Bridge::new(Id::try_from("bridge").expect("valid id"));
        bridge.push_bridge_part(BridgePartProperty::from_object(BridgePart::new(
            Id::try_from("bridge_part").expect("valid id"),
        )));
        bridge
    }

    #[test]
    fn test_iter_features_yields_bridge_and_its_parts() {
        let feature_types: Vec<FeatureType> = bridge_with_part()
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(
            feature_types,
            vec![FeatureType::Bridge, FeatureType::BridgePart]
        );
    }

    #[test]
    fn test_for_each_feature_mut_visits_bridge_and_its_parts() {
        let mut feature_types = Vec::new();
        bridge_with_part().for_each_feature_mut(&mut |f| feature_types.push(f.feature_type()));
        assert_eq!(
            feature_types,
            vec![FeatureType::Bridge, FeatureType::BridgePart]
        );
    }
}
