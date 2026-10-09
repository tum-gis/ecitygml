use crate::impl_try_from_occupied_space_kind_ref_mut_for_enum;
use crate::model::bridge::AbstractBridgeKind;
use crate::model::bridge::refs::AbstractBridgeKindRefMut;
use crate::model::building::AbstractBuildingKind;
use crate::model::building::refs::AbstractBuildingKindRefMut;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::construction::{
    AbstractConstruction, AbstractConstructionKind, AsAbstractConstruction,
    AsAbstractConstructionMut,
};
use crate::model::tunnel::AbstractTunnelKind;
use crate::model::tunnel::refs::AbstractTunnelKindRefMut;
use egml::model::common::RecomputeBoundingShape;

#[derive(Debug)]
pub enum AbstractConstructionKindRefMut<'a> {
    AbstractBuildingKind(AbstractBuildingKindRefMut<'a>),
    AbstractBridgeKind(AbstractBridgeKindRefMut<'a>),
    AbstractTunnelKind(AbstractTunnelKindRefMut<'a>),
}

impl<'a> From<&'a mut AbstractConstructionKind> for AbstractConstructionKindRefMut<'a> {
    fn from(item: &'a mut AbstractConstructionKind) -> Self {
        match item {
            AbstractConstructionKind::AbstractBuildingKind(x) => {
                Self::AbstractBuildingKind(x.into())
            }
            AbstractConstructionKind::AbstractBridgeKind(x) => Self::AbstractBridgeKind(x.into()),
            AbstractConstructionKind::AbstractTunnelKind(x) => Self::AbstractTunnelKind(x.into()),
        }
    }
}

impl<'a> AsAbstractConstruction for AbstractConstructionKindRefMut<'a> {
    fn abstract_construction(&self) -> &AbstractConstruction {
        match self {
            Self::AbstractBuildingKind(x) => x.abstract_construction(),
            Self::AbstractBridgeKind(x) => x.abstract_construction(),
            Self::AbstractTunnelKind(x) => x.abstract_construction(),
        }
    }
}

impl<'a> AsAbstractConstructionMut for AbstractConstructionKindRefMut<'a> {
    fn abstract_construction_mut(&mut self) -> &mut AbstractConstruction {
        match self {
            Self::AbstractBuildingKind(x) => x.abstract_construction_mut(),
            Self::AbstractBridgeKind(x) => x.abstract_construction_mut(),
            Self::AbstractTunnelKind(x) => x.abstract_construction_mut(),
        }
    }
}
crate::impl_abstract_construction_traits!(AbstractConstructionKindRefMut<'_>);
crate::impl_abstract_construction_mut_traits!(AbstractConstructionKindRefMut<'_>);

impl<'a> HasFeatureType for AbstractConstructionKindRefMut<'a> {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::AbstractBuildingKind(x) => x.feature_type(),
            Self::AbstractBridgeKind(x) => x.feature_type(),
            Self::AbstractTunnelKind(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_for_construction_kind_ref_mut {
    ($variant:ident, $type:ty) => {
        impl<'a> From<&'a mut $type>
            for $crate::model::construction::refs::AbstractConstructionKindRefMut<'a>
        {
            fn from(x: &'a mut $type) -> Self {
                $crate::model::construction::refs::AbstractConstructionKindRefMut::$variant(
                    x.into(),
                )
            }
        }
        $crate::impl_from_for_occupied_space_kind_ref_mut!(AbstractConstructionKind, $type);
    };
    ($variant:ident) => {
        $crate::impl_from_for_construction_kind_ref_mut!($variant, $variant);
    };
}
impl_from_for_construction_kind_ref_mut!(AbstractBuildingKind);
impl_from_for_construction_kind_ref_mut!(AbstractBridgeKind);
impl_from_for_construction_kind_ref_mut!(AbstractTunnelKind);

#[macro_export]
macro_rules! impl_try_from_for_construction_kind_ref_mut {
    ($variant:ident, $type:ty) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractConstructionKindRefMut<'a>>
            for &'a mut $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractConstructionKindRefMut<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractConstructionKindRefMut::$variant(
                        k,
                    ) => k.try_into().map_err(|_| ()),
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind_ref_mut!(AbstractConstructionKind, $type);
    };
}

#[macro_export]
macro_rules! impl_try_from_construction_kind_ref_mut_for_enum {
    ($variant:ident, $EnumRefMut:ident) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractConstructionKindRefMut<'a>>
            for $EnumRefMut<'a>
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractConstructionKindRefMut<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractConstructionKindRefMut::$variant(
                        k,
                    ) => $EnumRefMut::try_from(k).map_err(|_| ()),
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_occupied_space_kind_ref_mut_for_enum!(
            AbstractConstructionKind,
            $EnumRefMut
        );
    };
}
impl_try_from_occupied_space_kind_ref_mut_for_enum!(
    AbstractConstructionKind,
    AbstractConstructionKindRefMut
);

impl<'a> RecomputeBoundingShape for AbstractConstructionKindRefMut<'a> {
    fn recompute_bounding_shape(&mut self) {
        match self {
            Self::AbstractBuildingKind(x) => x.recompute_bounding_shape(),
            Self::AbstractBridgeKind(x) => x.recompute_bounding_shape(),
            Self::AbstractTunnelKind(x) => x.recompute_bounding_shape(),
        }
    }
}
