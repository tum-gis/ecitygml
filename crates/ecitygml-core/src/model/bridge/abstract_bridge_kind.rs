use crate::impl_abstract_bridge_mut_traits;
use crate::impl_abstract_bridge_traits;
use crate::model::bridge::{
    AbstractBridge, AsAbstractBridge, AsAbstractBridgeMut, Bridge, BridgePart,
};
use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub enum AbstractBridgeKind {
    Bridge(Bridge),
    BridgePart(BridgePart),
}

impl AsAbstractBridge for AbstractBridgeKind {
    fn abstract_bridge(&self) -> &AbstractBridge {
        match self {
            AbstractBridgeKind::Bridge(x) => x.abstract_bridge(),
            AbstractBridgeKind::BridgePart(x) => x.abstract_bridge(),
        }
    }
}

impl AsAbstractBridgeMut for AbstractBridgeKind {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge {
        match self {
            AbstractBridgeKind::Bridge(x) => x.abstract_bridge_mut(),
            AbstractBridgeKind::BridgePart(x) => x.abstract_bridge_mut(),
        }
    }
}

impl_abstract_bridge_traits!(AbstractBridgeKind);
impl_abstract_bridge_mut_traits!(AbstractBridgeKind);

impl HasFeatureType for AbstractBridgeKind {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::Bridge(x) => x.feature_type(),
            Self::BridgePart(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_bridge_kind {
    ($type:ident) => {
        impl From<$type> for $crate::model::bridge::AbstractBridgeKind {
            fn from(x: $type) -> Self {
                $crate::model::bridge::AbstractBridgeKind::$type(x)
            }
        }
        $crate::impl_from_for_construction_kind!(AbstractBridgeKind, $type);
    };
}
impl_from_bridge_kind!(Bridge);
impl_from_bridge_kind!(BridgePart);

#[macro_export]
macro_rules! impl_try_from_bridge_kind {
    ($type:ident) => {
        impl TryFrom<$crate::model::bridge::AbstractBridgeKind> for $type {
            type Error = ();
            fn try_from(x: $crate::model::bridge::AbstractBridgeKind) -> Result<Self, ()> {
                match x {
                    $crate::model::bridge::AbstractBridgeKind::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind!(AbstractBridgeKind, $type);
    };
}
impl_try_from_bridge_kind!(Bridge);
impl_try_from_bridge_kind!(BridgePart);

impl IterFeatures for AbstractBridgeKind {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        match self {
            AbstractBridgeKind::Bridge(x) => x.iter_features(),
            AbstractBridgeKind::BridgePart(x) => x.iter_features(),
        }
    }
}

impl ForEachFeatureMut for AbstractBridgeKind {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.for_each_feature_mut(f),
            AbstractBridgeKind::BridgePart(x) => x.for_each_feature_mut(f),
        }
    }
}

impl ComputeEnvelope for AbstractBridgeKind {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractBridgeKind::Bridge(x) => x.compute_envelope(),
            AbstractBridgeKind::BridgePart(x) => x.compute_envelope(),
        }
    }
}

impl ApplyTransform for AbstractBridgeKind {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.apply_transform(m),
            AbstractBridgeKind::BridgePart(x) => x.apply_transform(m),
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.apply_isometry(isometry),
            AbstractBridgeKind::BridgePart(x) => x.apply_isometry(isometry),
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.apply_translation(vector),
            AbstractBridgeKind::BridgePart(x) => x.apply_translation(vector),
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.apply_rotation(rotation),
            AbstractBridgeKind::BridgePart(x) => x.apply_rotation(rotation),
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        match self {
            AbstractBridgeKind::Bridge(x) => x.apply_scale(scale),
            AbstractBridgeKind::BridgePart(x) => x.apply_scale(scale),
        }
    }
}
