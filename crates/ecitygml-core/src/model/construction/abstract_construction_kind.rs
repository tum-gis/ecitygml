use crate::impl_abstract_construction_mut_traits;
use crate::impl_abstract_construction_traits;
use crate::model::bridge::AbstractBridgeKind;
use crate::model::building::AbstractBuildingKind;
use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};
use crate::model::construction::{
    AbstractConstruction, AsAbstractConstruction, AsAbstractConstructionMut, OtherConstruction,
};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::AbstractTunnelKind;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub enum AbstractConstructionKind {
    AbstractBuildingKind(AbstractBuildingKind),
    AbstractBridgeKind(AbstractBridgeKind),
    AbstractTunnelKind(AbstractTunnelKind),
    OtherConstruction(OtherConstruction),
}

impl AsAbstractConstruction for AbstractConstructionKind {
    fn abstract_construction(&self) -> &AbstractConstruction {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.abstract_construction(),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.abstract_construction(),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.abstract_construction(),
            AbstractConstructionKind::OtherConstruction(x) => x.abstract_construction(),
        }
    }
}

impl AsAbstractConstructionMut for AbstractConstructionKind {
    fn abstract_construction_mut(&mut self) -> &mut AbstractConstruction {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.abstract_construction_mut(),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.abstract_construction_mut(),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.abstract_construction_mut(),
            AbstractConstructionKind::OtherConstruction(x) => x.abstract_construction_mut(),
        }
    }
}

impl_abstract_construction_traits!(AbstractConstructionKind);
impl_abstract_construction_mut_traits!(AbstractConstructionKind);

impl HasFeatureType for AbstractConstructionKind {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::AbstractBuildingKind(x) => x.feature_type(),
            Self::AbstractBridgeKind(x) => x.feature_type(),
            Self::AbstractTunnelKind(x) => x.feature_type(),
            Self::OtherConstruction(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_for_construction_kind {
    ($variant:ident, $type:ty) => {
        impl From<$type> for $crate::model::construction::AbstractConstructionKind {
            fn from(x: $type) -> Self {
                $crate::model::construction::AbstractConstructionKind::$variant(x.into())
            }
        }
        $crate::impl_from_for_occupied_space_kind!(AbstractConstructionKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_from_for_construction_kind!($variant, $variant);
    };
}
impl_from_for_construction_kind!(AbstractBuildingKind);
impl_from_for_construction_kind!(AbstractBridgeKind);
impl_from_for_construction_kind!(AbstractTunnelKind);
impl_from_for_construction_kind!(OtherConstruction);

#[macro_export]
macro_rules! impl_try_from_for_construction_kind {
    ($variant:ident, $type:ty) => {
        impl TryFrom<$crate::model::construction::AbstractConstructionKind> for $type {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::AbstractConstructionKind,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::AbstractConstructionKind::$variant(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind!(AbstractConstructionKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_try_from_for_construction_kind!($variant, $variant);
    };
}
impl_try_from_for_construction_kind!(AbstractBuildingKind);
impl_try_from_for_construction_kind!(AbstractBridgeKind);
impl_try_from_for_construction_kind!(AbstractTunnelKind);
impl_try_from_for_construction_kind!(OtherConstruction);

impl IterFeatures for AbstractConstructionKind {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.iter_features(),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.iter_features(),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.iter_features(),
            AbstractConstructionKind::OtherConstruction(x) => x.iter_features(),
        }
    }
}

impl ForEachFeatureMut for AbstractConstructionKind {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.for_each_feature_mut(f),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.for_each_feature_mut(f),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.for_each_feature_mut(f),
            AbstractConstructionKind::OtherConstruction(x) => x.for_each_feature_mut(f),
        }
    }
}

impl ComputeEnvelope for AbstractConstructionKind {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.compute_envelope(),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.compute_envelope(),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.compute_envelope(),
            AbstractConstructionKind::OtherConstruction(x) => x.compute_envelope(),
        }
    }
}

impl ApplyTransform for AbstractConstructionKind {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.apply_transform(m),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.apply_transform(m),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.apply_transform(m),
            AbstractConstructionKind::OtherConstruction(x) => x.apply_transform(m),
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.apply_isometry(isometry),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.apply_isometry(isometry),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.apply_isometry(isometry),
            AbstractConstructionKind::OtherConstruction(x) => x.apply_isometry(isometry),
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.apply_translation(vector),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.apply_translation(vector),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.apply_translation(vector),
            AbstractConstructionKind::OtherConstruction(x) => x.apply_translation(vector),
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.apply_rotation(rotation),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.apply_rotation(rotation),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.apply_rotation(rotation),
            AbstractConstructionKind::OtherConstruction(x) => x.apply_rotation(rotation),
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        match self {
            AbstractConstructionKind::AbstractBuildingKind(x) => x.apply_scale(scale),
            AbstractConstructionKind::AbstractBridgeKind(x) => x.apply_scale(scale),
            AbstractConstructionKind::AbstractTunnelKind(x) => x.apply_scale(scale),
            AbstractConstructionKind::OtherConstruction(x) => x.apply_scale(scale),
        }
    }
}
