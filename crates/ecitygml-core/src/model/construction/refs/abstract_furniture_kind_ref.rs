use crate::impl_try_from_occupied_space_kind_ref_for_enum;
use crate::model::bridge::BridgeFurniture;
use crate::model::building::BuildingFurniture;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::construction::{AbstractFurniture, AbstractFurnitureKind, AsAbstractFurniture};
use crate::model::tunnel::TunnelFurniture;
use egml::model::common::ComputeEnvelope;
use egml::model::geometry::Envelope;

#[derive(Debug, Clone, Copy)]
pub enum AbstractFurnitureKindRef<'a> {
    BridgeFurniture(&'a BridgeFurniture),
    BuildingFurniture(&'a BuildingFurniture),
    TunnelFurniture(&'a TunnelFurniture),
}

impl<'a> From<&'a AbstractFurnitureKind> for AbstractFurnitureKindRef<'a> {
    fn from(item: &'a AbstractFurnitureKind) -> Self {
        match item {
            AbstractFurnitureKind::BridgeFurniture(x) => Self::BridgeFurniture(x),
            AbstractFurnitureKind::BuildingFurniture(x) => Self::BuildingFurniture(x),
            AbstractFurnitureKind::TunnelFurniture(x) => Self::TunnelFurniture(x),
        }
    }
}

impl<'a> AsAbstractFurniture for AbstractFurnitureKindRef<'a> {
    fn abstract_furniture(&self) -> &AbstractFurniture {
        match self {
            Self::BridgeFurniture(x) => x.abstract_furniture(),
            Self::BuildingFurniture(x) => x.abstract_furniture(),
            Self::TunnelFurniture(x) => x.abstract_furniture(),
        }
    }
}
crate::impl_abstract_furniture_traits!(AbstractFurnitureKindRef<'_>);

impl<'a> HasFeatureType for AbstractFurnitureKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::BridgeFurniture(_) => FeatureType::BridgeFurniture,
            Self::BuildingFurniture(_) => FeatureType::BuildingFurniture,
            Self::TunnelFurniture(_) => FeatureType::TunnelFurniture,
        }
    }
}

#[macro_export]
macro_rules! impl_from_furniture_kind_ref {
    ($type:ident) => {
        impl<'a> From<&'a $type>
            for $crate::model::construction::refs::AbstractFurnitureKindRef<'a>
        {
            fn from(x: &'a $type) -> Self {
                $crate::model::construction::refs::AbstractFurnitureKindRef::$type(x.into())
            }
        }
        $crate::impl_from_for_occupied_space_kind_ref!(AbstractFurnitureKind, $type);
    };
}
impl_from_furniture_kind_ref!(BridgeFurniture);
impl_from_furniture_kind_ref!(BuildingFurniture);
impl_from_furniture_kind_ref!(TunnelFurniture);

#[macro_export]
macro_rules! impl_try_from_furniture_kind_ref {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractFurnitureKindRef<'a>>
            for &'a $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractFurnitureKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractFurnitureKindRef::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind_ref!(AbstractFurnitureKind, $type);
    };
}
impl_try_from_furniture_kind_ref!(BridgeFurniture);
impl_try_from_furniture_kind_ref!(BuildingFurniture);
impl_try_from_furniture_kind_ref!(TunnelFurniture);
impl_try_from_occupied_space_kind_ref_for_enum!(AbstractFurnitureKind, AbstractFurnitureKindRef);

impl<'a> ComputeEnvelope for AbstractFurnitureKindRef<'a> {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractFurnitureKindRef::BridgeFurniture(x) => x.compute_envelope(),
            AbstractFurnitureKindRef::BuildingFurniture(x) => x.compute_envelope(),
            AbstractFurnitureKindRef::TunnelFurniture(x) => x.compute_envelope(),
        }
    }
}
