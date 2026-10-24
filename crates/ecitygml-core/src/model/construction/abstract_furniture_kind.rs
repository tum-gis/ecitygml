use crate::impl_abstract_furniture_mut_traits;
use crate::impl_abstract_furniture_traits;
use crate::model::bridge::BridgeFurniture;
use crate::model::building::BuildingFurniture;
use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};
use crate::model::construction::{AbstractFurniture, AsAbstractFurniture, AsAbstractFurnitureMut};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::TunnelFurniture;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub enum AbstractFurnitureKind {
    BridgeFurniture(BridgeFurniture),
    BuildingFurniture(BuildingFurniture),
    TunnelFurniture(TunnelFurniture),
}

impl AsAbstractFurniture for AbstractFurnitureKind {
    fn abstract_furniture(&self) -> &AbstractFurniture {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.abstract_furniture(),
            AbstractFurnitureKind::BuildingFurniture(x) => x.abstract_furniture(),
            AbstractFurnitureKind::TunnelFurniture(x) => x.abstract_furniture(),
        }
    }
}

impl AsAbstractFurnitureMut for AbstractFurnitureKind {
    fn abstract_furniture_mut(&mut self) -> &mut AbstractFurniture {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.abstract_furniture_mut(),
            AbstractFurnitureKind::BuildingFurniture(x) => x.abstract_furniture_mut(),
            AbstractFurnitureKind::TunnelFurniture(x) => x.abstract_furniture_mut(),
        }
    }
}

impl_abstract_furniture_traits!(AbstractFurnitureKind);
impl_abstract_furniture_mut_traits!(AbstractFurnitureKind);

impl HasFeatureType for AbstractFurnitureKind {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::BridgeFurniture(x) => x.feature_type(),
            Self::BuildingFurniture(x) => x.feature_type(),
            Self::TunnelFurniture(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_furniture_kind {
    ($type:ident) => {
        impl From<$type> for $crate::model::construction::AbstractFurnitureKind {
            fn from(x: $type) -> Self {
                $crate::model::construction::AbstractFurnitureKind::$type(x)
            }
        }
        $crate::impl_from_for_occupied_space_kind!(AbstractFurnitureKind, $type);
    };
}
impl_from_furniture_kind!(BridgeFurniture);
impl_from_furniture_kind!(BuildingFurniture);
impl_from_furniture_kind!(TunnelFurniture);

#[macro_export]
macro_rules! impl_try_from_furniture_kind {
    ($type:ident) => {
        impl TryFrom<$crate::model::construction::AbstractFurnitureKind> for $type {
            type Error = ();
            fn try_from(x: $crate::model::construction::AbstractFurnitureKind) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::AbstractFurnitureKind::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind!(AbstractFurnitureKind, $type);
    };
}
impl_try_from_furniture_kind!(BridgeFurniture);
impl_try_from_furniture_kind!(BuildingFurniture);
impl_try_from_furniture_kind!(TunnelFurniture);

impl IterFeatures for AbstractFurnitureKind {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.iter_features(),
            AbstractFurnitureKind::BuildingFurniture(x) => x.iter_features(),
            AbstractFurnitureKind::TunnelFurniture(x) => x.iter_features(),
        }
    }
}

impl ForEachFeatureMut for AbstractFurnitureKind {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.for_each_feature_mut(f),
            AbstractFurnitureKind::BuildingFurniture(x) => x.for_each_feature_mut(f),
            AbstractFurnitureKind::TunnelFurniture(x) => x.for_each_feature_mut(f),
        }
    }
}

impl ComputeEnvelope for AbstractFurnitureKind {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.compute_envelope(),
            AbstractFurnitureKind::BuildingFurniture(x) => x.compute_envelope(),
            AbstractFurnitureKind::TunnelFurniture(x) => x.compute_envelope(),
        }
    }
}

impl ApplyTransform for AbstractFurnitureKind {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.apply_transform(m),
            AbstractFurnitureKind::BuildingFurniture(x) => x.apply_transform(m),
            AbstractFurnitureKind::TunnelFurniture(x) => x.apply_transform(m),
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.apply_isometry(isometry),
            AbstractFurnitureKind::BuildingFurniture(x) => x.apply_isometry(isometry),
            AbstractFurnitureKind::TunnelFurniture(x) => x.apply_isometry(isometry),
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.apply_translation(vector),
            AbstractFurnitureKind::BuildingFurniture(x) => x.apply_translation(vector),
            AbstractFurnitureKind::TunnelFurniture(x) => x.apply_translation(vector),
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.apply_rotation(rotation),
            AbstractFurnitureKind::BuildingFurniture(x) => x.apply_rotation(rotation),
            AbstractFurnitureKind::TunnelFurniture(x) => x.apply_rotation(rotation),
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        match self {
            AbstractFurnitureKind::BridgeFurniture(x) => x.apply_scale(scale),
            AbstractFurnitureKind::BuildingFurniture(x) => x.apply_scale(scale),
            AbstractFurnitureKind::TunnelFurniture(x) => x.apply_scale(scale),
        }
    }
}
