use crate::impl_try_from_physical_space_kind_ref_for_enum;
use crate::model::bridge::BridgeRoom;
use crate::model::building::BuildingRoom;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::core::{
    AbstractUnoccupiedSpace, AbstractUnoccupiedSpaceKind, AsAbstractUnoccupiedSpace,
};
use crate::model::generics::GenericUnoccupiedSpace;
use crate::model::transportation::refs::AbstractTransportationSpaceKindRef;
use crate::model::transportation::{
    AbstractTransportationSpaceKind, AuxiliaryTrafficSpace, ClearanceSpace, Hole, TrafficSpace,
};
use crate::model::tunnel::HollowSpace;
use egml::model::common::ComputeEnvelope;
use egml::model::geometry::Envelope;

#[derive(Debug, Clone, Copy)]
pub enum AbstractUnoccupiedSpaceKindRef<'a> {
    AuxiliaryTrafficSpace(&'a AuxiliaryTrafficSpace),
    BridgeRoom(&'a BridgeRoom),
    BuildingRoom(&'a BuildingRoom),
    ClearanceSpace(&'a ClearanceSpace),
    GenericUnoccupiedSpace(&'a GenericUnoccupiedSpace),
    Hole(&'a Hole),
    HollowSpace(&'a HollowSpace),
    TrafficSpace(&'a TrafficSpace),
    AbstractTransportationSpaceKind(AbstractTransportationSpaceKindRef<'a>),
}

impl<'a> From<&'a AbstractUnoccupiedSpaceKind> for AbstractUnoccupiedSpaceKindRef<'a> {
    fn from(item: &'a AbstractUnoccupiedSpaceKind) -> Self {
        match item {
            AbstractUnoccupiedSpaceKind::AuxiliaryTrafficSpace(x) => Self::AuxiliaryTrafficSpace(x),
            AbstractUnoccupiedSpaceKind::BridgeRoom(x) => Self::BridgeRoom(x),
            AbstractUnoccupiedSpaceKind::BuildingRoom(x) => Self::BuildingRoom(x),
            AbstractUnoccupiedSpaceKind::ClearanceSpace(x) => Self::ClearanceSpace(x),
            AbstractUnoccupiedSpaceKind::GenericUnoccupiedSpace(x) => {
                Self::GenericUnoccupiedSpace(x)
            }
            AbstractUnoccupiedSpaceKind::Hole(x) => Self::Hole(x),
            AbstractUnoccupiedSpaceKind::HollowSpace(x) => Self::HollowSpace(x),
            AbstractUnoccupiedSpaceKind::TrafficSpace(x) => Self::TrafficSpace(x),
            AbstractUnoccupiedSpaceKind::AbstractTransportationSpaceKind(x) => {
                Self::AbstractTransportationSpaceKind(x.into())
            }
        }
    }
}

impl<'a> AsAbstractUnoccupiedSpace for AbstractUnoccupiedSpaceKindRef<'a> {
    fn abstract_unoccupied_space(&self) -> &AbstractUnoccupiedSpace {
        match self {
            Self::AuxiliaryTrafficSpace(x) => x.abstract_unoccupied_space(),
            Self::BridgeRoom(x) => x.abstract_unoccupied_space(),
            Self::BuildingRoom(x) => x.abstract_unoccupied_space(),
            Self::ClearanceSpace(x) => x.abstract_unoccupied_space(),
            Self::GenericUnoccupiedSpace(x) => x.abstract_unoccupied_space(),
            Self::Hole(x) => x.abstract_unoccupied_space(),
            Self::HollowSpace(x) => x.abstract_unoccupied_space(),
            Self::TrafficSpace(x) => x.abstract_unoccupied_space(),
            Self::AbstractTransportationSpaceKind(x) => x.abstract_unoccupied_space(),
        }
    }
}
crate::impl_abstract_unoccupied_space_traits!(AbstractUnoccupiedSpaceKindRef<'_>);

impl<'a> HasFeatureType for AbstractUnoccupiedSpaceKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::AuxiliaryTrafficSpace(_) => FeatureType::AuxiliaryTrafficSpace,
            Self::BridgeRoom(_) => FeatureType::BridgeRoom,
            Self::BuildingRoom(_) => FeatureType::BuildingRoom,
            Self::ClearanceSpace(_) => FeatureType::ClearanceSpace,
            Self::GenericUnoccupiedSpace(_) => FeatureType::GenericUnoccupiedSpace,
            Self::Hole(_) => FeatureType::Hole,
            Self::HollowSpace(_) => FeatureType::HollowSpace,
            Self::TrafficSpace(_) => FeatureType::TrafficSpace,
            Self::AbstractTransportationSpaceKind(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_for_unoccupied_space_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> From<&'a $type> for $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef<'a> {
            fn from(x: &'a $type) -> Self {
                $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef::$variant(x.into())
            }
        }
        $crate::impl_from_for_physical_space_kind_ref!(AbstractUnoccupiedSpaceKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_from_for_unoccupied_space_kind_ref!($variant, $variant);
    };
}
impl_from_for_unoccupied_space_kind_ref!(AuxiliaryTrafficSpace);
impl_from_for_unoccupied_space_kind_ref!(BridgeRoom);
impl_from_for_unoccupied_space_kind_ref!(BuildingRoom);
impl_from_for_unoccupied_space_kind_ref!(ClearanceSpace);
impl_from_for_unoccupied_space_kind_ref!(GenericUnoccupiedSpace);
impl_from_for_unoccupied_space_kind_ref!(Hole);
impl_from_for_unoccupied_space_kind_ref!(HollowSpace);
impl_from_for_unoccupied_space_kind_ref!(TrafficSpace);
impl_from_for_unoccupied_space_kind_ref!(AbstractTransportationSpaceKind);

#[macro_export]
macro_rules! impl_try_from_for_unoccupied_space_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> TryFrom<$crate::model::core::refs::AbstractUnoccupiedSpaceKindRef<'a>>
            for &'a $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef::$variant(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_physical_space_kind_ref!(AbstractUnoccupiedSpaceKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_try_from_for_unoccupied_space_kind_ref!($variant, $variant);
    };
}
impl_try_from_for_unoccupied_space_kind_ref!(AuxiliaryTrafficSpace);
impl_try_from_for_unoccupied_space_kind_ref!(BridgeRoom);
impl_try_from_for_unoccupied_space_kind_ref!(BuildingRoom);
impl_try_from_for_unoccupied_space_kind_ref!(ClearanceSpace);
impl_try_from_for_unoccupied_space_kind_ref!(GenericUnoccupiedSpace);
impl_try_from_for_unoccupied_space_kind_ref!(Hole);
impl_try_from_for_unoccupied_space_kind_ref!(HollowSpace);
impl_try_from_for_unoccupied_space_kind_ref!(TrafficSpace);

#[macro_export]
macro_rules! impl_try_from_unoccupied_space_kind_ref_for_enum {
    ($variant:ident, $EnumRef:ident) => {
        impl<'a> TryFrom<$crate::model::core::refs::AbstractUnoccupiedSpaceKindRef<'a>>
            for $EnumRef<'a>
        {
            type Error = ();
            fn try_from(
                x: $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::core::refs::AbstractUnoccupiedSpaceKindRef::$variant(k) => {
                        $EnumRef::try_from(k).map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_physical_space_kind_ref_for_enum!(
            AbstractUnoccupiedSpaceKind,
            $EnumRef
        );
    };
}
impl_try_from_physical_space_kind_ref_for_enum!(
    AbstractUnoccupiedSpaceKind,
    AbstractUnoccupiedSpaceKindRef
);

impl<'a> ComputeEnvelope for AbstractUnoccupiedSpaceKindRef<'a> {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractUnoccupiedSpaceKindRef::AuxiliaryTrafficSpace(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::BridgeRoom(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::BuildingRoom(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::ClearanceSpace(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::GenericUnoccupiedSpace(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::Hole(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::HollowSpace(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::TrafficSpace(x) => x.compute_envelope(),
            AbstractUnoccupiedSpaceKindRef::AbstractTransportationSpaceKind(x) => {
                x.compute_envelope()
            }
        }
    }
}
