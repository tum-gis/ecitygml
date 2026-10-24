use crate::impl_try_from_occupied_space_kind_ref_mut_for_enum;
use crate::model::bridge::BridgeFurniture;
use crate::model::building::BuildingFurniture;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::construction::{
    AbstractFurniture, AbstractFurnitureKind, AsAbstractFurniture, AsAbstractFurnitureMut,
};
use crate::model::tunnel::TunnelFurniture;
use egml::model::common::RecomputeBoundingShape;

#[derive(Debug)]
pub enum AbstractFurnitureKindRefMut<'a> {
    BridgeFurniture(&'a mut BridgeFurniture),
    BuildingFurniture(&'a mut BuildingFurniture),
    TunnelFurniture(&'a mut TunnelFurniture),
}

impl<'a> From<&'a mut AbstractFurnitureKind> for AbstractFurnitureKindRefMut<'a> {
    fn from(item: &'a mut AbstractFurnitureKind) -> Self {
        match item {
            AbstractFurnitureKind::BridgeFurniture(x) => Self::BridgeFurniture(x),
            AbstractFurnitureKind::BuildingFurniture(x) => Self::BuildingFurniture(x),
            AbstractFurnitureKind::TunnelFurniture(x) => Self::TunnelFurniture(x),
        }
    }
}

impl<'a> AsAbstractFurniture for AbstractFurnitureKindRefMut<'a> {
    fn abstract_furniture(&self) -> &AbstractFurniture {
        match self {
            Self::BridgeFurniture(x) => x.abstract_furniture(),
            Self::BuildingFurniture(x) => x.abstract_furniture(),
            Self::TunnelFurniture(x) => x.abstract_furniture(),
        }
    }
}

impl<'a> AsAbstractFurnitureMut for AbstractFurnitureKindRefMut<'a> {
    fn abstract_furniture_mut(&mut self) -> &mut AbstractFurniture {
        match self {
            Self::BridgeFurniture(x) => x.abstract_furniture_mut(),
            Self::BuildingFurniture(x) => x.abstract_furniture_mut(),
            Self::TunnelFurniture(x) => x.abstract_furniture_mut(),
        }
    }
}
crate::impl_abstract_furniture_traits!(AbstractFurnitureKindRefMut<'_>);
crate::impl_abstract_furniture_mut_traits!(AbstractFurnitureKindRefMut<'_>);

impl<'a> HasFeatureType for AbstractFurnitureKindRefMut<'a> {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::BridgeFurniture(x) => x.feature_type(),
            Self::BuildingFurniture(x) => x.feature_type(),
            Self::TunnelFurniture(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_furniture_kind_ref_mut {
    ($type:ident) => {
        impl<'a> From<&'a mut $type>
            for $crate::model::construction::refs::AbstractFurnitureKindRefMut<'a>
        {
            fn from(x: &'a mut $type) -> Self {
                $crate::model::construction::refs::AbstractFurnitureKindRefMut::$type(x.into())
            }
        }
        $crate::impl_from_for_occupied_space_kind_ref_mut!(AbstractFurnitureKind, $type);
    };
}
impl_from_furniture_kind_ref_mut!(BridgeFurniture);
impl_from_furniture_kind_ref_mut!(BuildingFurniture);
impl_from_furniture_kind_ref_mut!(TunnelFurniture);

#[macro_export]
macro_rules! impl_try_from_furniture_kind_ref_mut {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::construction::refs::AbstractFurnitureKindRefMut<'a>>
            for &'a mut $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::construction::refs::AbstractFurnitureKindRefMut<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::construction::refs::AbstractFurnitureKindRefMut::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_occupied_space_kind_ref_mut!(AbstractFurnitureKind, $type);
    };
}
impl_try_from_furniture_kind_ref_mut!(BridgeFurniture);
impl_try_from_furniture_kind_ref_mut!(BuildingFurniture);
impl_try_from_furniture_kind_ref_mut!(TunnelFurniture);
impl_try_from_occupied_space_kind_ref_mut_for_enum!(
    AbstractFurnitureKind,
    AbstractFurnitureKindRefMut
);

impl<'a> RecomputeBoundingShape for AbstractFurnitureKindRefMut<'a> {
    fn recompute_bounding_shape(&mut self) {
        match self {
            Self::BridgeFurniture(x) => x.recompute_bounding_shape(),
            Self::BuildingFurniture(x) => x.recompute_bounding_shape(),
            Self::TunnelFurniture(x) => x.recompute_bounding_shape(),
        }
    }
}
