use crate::impl_try_from_space_kind_ref_for_enum;
use crate::model::building::AbstractBuildingSubdivisionKind;
use crate::model::building::refs::AbstractBuildingSubdivisionKindRef;
use crate::model::city_object_group::CityObjectGroup;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::core::{AbstractLogicalSpace, AbstractLogicalSpaceKind, AsAbstractLogicalSpace};
use crate::model::generics::GenericLogicalSpace;
use egml::model::common::ComputeEnvelope;
use egml::model::geometry::Envelope;

#[derive(Debug, Clone, Copy)]
pub enum AbstractLogicalSpaceKindRef<'a> {
    AbstractBuildingSubdivisionKind(AbstractBuildingSubdivisionKindRef<'a>),
    CityObjectGroup(&'a CityObjectGroup),
    GenericLogicalSpace(&'a GenericLogicalSpace),
}

impl<'a> From<&'a AbstractLogicalSpaceKind> for AbstractLogicalSpaceKindRef<'a> {
    fn from(item: &'a AbstractLogicalSpaceKind) -> Self {
        match item {
            AbstractLogicalSpaceKind::AbstractBuildingSubdivisionKind(x) => {
                Self::AbstractBuildingSubdivisionKind(x.into())
            }
            AbstractLogicalSpaceKind::CityObjectGroup(x) => Self::CityObjectGroup(x),
            AbstractLogicalSpaceKind::GenericLogicalSpace(x) => Self::GenericLogicalSpace(x),
        }
    }
}

impl<'a> AsAbstractLogicalSpace for AbstractLogicalSpaceKindRef<'a> {
    fn abstract_logical_space(&self) -> &AbstractLogicalSpace {
        match self {
            Self::AbstractBuildingSubdivisionKind(x) => x.abstract_logical_space(),
            Self::CityObjectGroup(x) => x.abstract_logical_space(),
            Self::GenericLogicalSpace(x) => x.abstract_logical_space(),
        }
    }
}
crate::impl_abstract_logical_space_traits!(AbstractLogicalSpaceKindRef<'_>);

impl<'a> HasFeatureType for AbstractLogicalSpaceKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::AbstractBuildingSubdivisionKind(x) => x.feature_type(),
            Self::CityObjectGroup(x) => x.feature_type(),
            Self::GenericLogicalSpace(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_for_logical_space_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> From<&'a $type> for $crate::model::core::refs::AbstractLogicalSpaceKindRef<'a> {
            fn from(x: &'a $type) -> Self {
                $crate::model::core::refs::AbstractLogicalSpaceKindRef::$variant(x.into())
            }
        }
        $crate::impl_from_for_space_kind_ref!(AbstractLogicalSpaceKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_from_for_logical_space_kind_ref!($variant, $variant);
    };
}
impl_from_for_logical_space_kind_ref!(AbstractBuildingSubdivisionKind);
impl_from_for_logical_space_kind_ref!(CityObjectGroup);
impl_from_for_logical_space_kind_ref!(GenericLogicalSpace);

#[macro_export]
macro_rules! impl_try_from_for_logical_space_kind_ref {
    ($variant:ident, $type:ty) => {
        impl<'a> TryFrom<$crate::model::core::refs::AbstractLogicalSpaceKindRef<'a>> for &'a $type {
            type Error = ();
            fn try_from(
                x: $crate::model::core::refs::AbstractLogicalSpaceKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::core::refs::AbstractLogicalSpaceKindRef::$variant(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_space_kind_ref!(AbstractLogicalSpaceKind, $type);
    };
}
impl_try_from_for_logical_space_kind_ref!(CityObjectGroup, CityObjectGroup);
impl_try_from_for_logical_space_kind_ref!(GenericLogicalSpace, GenericLogicalSpace);

#[macro_export]
macro_rules! impl_try_from_logical_space_kind_ref_for_enum {
    ($variant:ident, $EnumRef:ident) => {
        impl<'a> TryFrom<$crate::model::core::refs::AbstractLogicalSpaceKindRef<'a>>
            for $EnumRef<'a>
        {
            type Error = ();
            fn try_from(
                x: $crate::model::core::refs::AbstractLogicalSpaceKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::core::refs::AbstractLogicalSpaceKindRef::$variant(k) => {
                        $EnumRef::try_from(k).map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_space_kind_ref_for_enum!(AbstractLogicalSpaceKind, $EnumRef);
    };
}
impl_try_from_space_kind_ref_for_enum!(AbstractLogicalSpaceKind, AbstractLogicalSpaceKindRef);

impl<'a> ComputeEnvelope for AbstractLogicalSpaceKindRef<'a> {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractLogicalSpaceKindRef::AbstractBuildingSubdivisionKind(x) => x.compute_envelope(),
            AbstractLogicalSpaceKindRef::CityObjectGroup(x) => x.compute_envelope(),
            AbstractLogicalSpaceKindRef::GenericLogicalSpace(x) => x.compute_envelope(),
        }
    }
}
