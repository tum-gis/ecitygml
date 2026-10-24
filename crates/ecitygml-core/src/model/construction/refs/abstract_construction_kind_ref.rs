use crate::impl_try_from_occupied_space_kind_ref_for_enum;
use crate::model::bridge::AbstractBridgeKind;
use crate::model::bridge::refs::AbstractBridgeKindRef;
use crate::model::building::AbstractBuildingKind;
use crate::model::building::refs::AbstractBuildingKindRef;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::construction::{
    AbstractConstruction, AbstractConstructionKind, AsAbstractConstruction, OtherConstruction,
};
use crate::model::tunnel::AbstractTunnelKind;
use crate::model::tunnel::refs::AbstractTunnelKindRef;
use egml::model::common::ComputeEnvelope;
use egml::model::geometry::Envelope;

#[derive(Debug, Clone, Copy)]
pub enum AbstractConstructionKindRef<'a> {
    AbstractBuildingKind(AbstractBuildingKindRef<'a>),
    AbstractBridgeKind(AbstractBridgeKindRef<'a>),
    AbstractTunnelKind(AbstractTunnelKindRef<'a>),
    OtherConstruction(&'a OtherConstruction),
}

impl<'a> From<&'a AbstractConstructionKind> for AbstractConstructionKindRef<'a> {
    fn from(item: &'a AbstractConstructionKind) -> Self {
        match item {
            AbstractConstructionKind::AbstractBuildingKind(x) => {
                Self::AbstractBuildingKind(x.into())
            }
            AbstractConstructionKind::AbstractBridgeKind(x) => Self::AbstractBridgeKind(x.into()),
            AbstractConstructionKind::AbstractTunnelKind(x) => Self::AbstractTunnelKind(x.into()),
            AbstractConstructionKind::OtherConstruction(x) => Self::OtherConstruction(x),
        }
    }
}

impl<'a> AsAbstractConstruction for AbstractConstructionKindRef<'a> {
    fn abstract_construction(&self) -> &AbstractConstruction {
        match self {
            Self::AbstractBuildingKind(x) => x.abstract_construction(),
            Self::AbstractBridgeKind(x) => x.abstract_construction(),
            Self::AbstractTunnelKind(x) => x.abstract_construction(),
            Self::OtherConstruction(x) => x.abstract_construction(),
        }
    }
}
crate::impl_abstract_construction_traits!(AbstractConstructionKindRef<'_>);

impl<'a> HasFeatureType for AbstractConstructionKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::AbstractBuildingKind(x) => x.feature_type(),
            Self::AbstractBridgeKind(x) => x.feature_type(),
            Self::AbstractTunnelKind(x) => x.feature_type(),
            Self::OtherConstruction(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_for_construction_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> From<&'a $type>
            for $crate::model::construction::refs::AbstractConstructionKindRef<'a>
        {
            fn from(x: &'a $type) -> Self {
                $crate::model::construction::refs::AbstractConstructionKindRef::$variant(x.into())
            }
        }
        $crate::impl_from_for_occupied_space_kind_ref!(AbstractConstructionKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_from_for_construction_kind_ref!($variant, $variant);
    };
}
impl_from_for_construction_kind_ref!(AbstractBuildingKind);
impl_from_for_construction_kind_ref!(AbstractBridgeKind);
impl_from_for_construction_kind_ref!(AbstractTunnelKind);
impl_from_for_construction_kind_ref!(OtherConstruction);

#[macro_export]
macro_rules! impl_try_from_for_construction_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractConstructionKindRef<'a>>
            for &'a $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractConstructionKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractConstructionKindRef::$variant(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind_ref!(AbstractConstructionKind, $type);
    };
}

impl_try_from_for_construction_kind_ref!(OtherConstruction, OtherConstruction);

#[macro_export]
macro_rules! impl_try_from_construction_kind_ref_for_enum {
    ($variant:ident, $EnumRef:ident) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractConstructionKindRef<'a>>
            for $EnumRef<'a>
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractConstructionKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractConstructionKindRef::$variant(k) => {
                        $EnumRef::try_from(k).map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_occupied_space_kind_ref_for_enum!(AbstractConstructionKind, $EnumRef);
    };
}
impl_try_from_occupied_space_kind_ref_for_enum!(
    AbstractConstructionKind,
    AbstractConstructionKindRef
);

impl<'a> ComputeEnvelope for AbstractConstructionKindRef<'a> {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractConstructionKindRef::AbstractBuildingKind(x) => x.compute_envelope(),
            AbstractConstructionKindRef::AbstractBridgeKind(x) => x.compute_envelope(),
            AbstractConstructionKindRef::AbstractTunnelKind(x) => x.compute_envelope(),
            AbstractConstructionKindRef::OtherConstruction(x) => x.compute_envelope(),
        }
    }
}
