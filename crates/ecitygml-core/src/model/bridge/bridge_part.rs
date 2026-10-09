use crate::model::bridge::{AbstractBridge, AsAbstractBridge, AsAbstractBridgeMut};
use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct BridgePart {
    pub(crate) abstract_bridge: AbstractBridge,
}

impl BridgePart {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_bridge(AbstractBridge::new(id))
    }

    pub fn from_abstract_bridge(abstract_bridge: AbstractBridge) -> Self {
        Self { abstract_bridge }
    }
}

impl AsAbstractBridge for BridgePart {
    fn abstract_bridge(&self) -> &AbstractBridge {
        &self.abstract_bridge
    }
}

impl AsAbstractBridgeMut for BridgePart {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge {
        &mut self.abstract_bridge
    }
}

crate::impl_abstract_bridge_traits!(BridgePart);
crate::impl_abstract_bridge_mut_traits!(BridgePart);
crate::impl_has_feature_type!(BridgePart, BridgePart);

impl IterFeatures for BridgePart {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_bridge.iter_features()))
    }
}

impl ForEachFeatureMut for BridgePart {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_bridge.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for BridgePart {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_bridge.compute_envelope()
    }
}

impl ApplyTransform for BridgePart {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_bridge.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_bridge.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_bridge.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_bridge.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_bridge.apply_scale(scale);
    }
}
