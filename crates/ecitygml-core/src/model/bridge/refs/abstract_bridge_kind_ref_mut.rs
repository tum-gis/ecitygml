use crate::impl_try_from_construction_kind_ref_mut_for_enum;
use crate::model::bridge::{
    AbstractBridge, AbstractBridgeKind, AsAbstractBridge, AsAbstractBridgeMut, Bridge, BridgePart,
};
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use egml::model::common::RecomputeBoundingShape;

#[derive(Debug)]
pub enum AbstractBridgeKindRefMut<'a> {
    Bridge(&'a mut Bridge),
    BridgePart(&'a mut BridgePart),
}

impl<'a> From<&'a mut AbstractBridgeKind> for AbstractBridgeKindRefMut<'a> {
    fn from(item: &'a mut AbstractBridgeKind) -> Self {
        match item {
            AbstractBridgeKind::Bridge(x) => Self::Bridge(x),
            AbstractBridgeKind::BridgePart(x) => Self::BridgePart(x),
        }
    }
}

impl<'a> AsAbstractBridge for AbstractBridgeKindRefMut<'a> {
    fn abstract_bridge(&self) -> &AbstractBridge {
        match self {
            Self::Bridge(x) => x.abstract_bridge(),
            Self::BridgePart(x) => x.abstract_bridge(),
        }
    }
}

impl<'a> AsAbstractBridgeMut for AbstractBridgeKindRefMut<'a> {
    fn abstract_bridge_mut(&mut self) -> &mut AbstractBridge {
        match self {
            Self::Bridge(x) => x.abstract_bridge_mut(),
            Self::BridgePart(x) => x.abstract_bridge_mut(),
        }
    }
}
crate::impl_abstract_bridge_traits!(AbstractBridgeKindRefMut<'_>);
crate::impl_abstract_bridge_mut_traits!(AbstractBridgeKindRefMut<'_>);

impl<'a> HasFeatureType for AbstractBridgeKindRefMut<'a> {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::Bridge(x) => x.feature_type(),
            Self::BridgePart(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_bridge_kind_ref_mut {
    ($type:ident) => {
        impl<'a> From<&'a mut $type> for $crate::model::bridge::refs::AbstractBridgeKindRefMut<'a> {
            fn from(x: &'a mut $type) -> Self {
                $crate::model::bridge::refs::AbstractBridgeKindRefMut::$type(x.into())
            }
        }
        $crate::impl_from_for_construction_kind_ref_mut!(AbstractBridgeKind, $type);
    };
}
impl_from_bridge_kind_ref_mut!(Bridge);
impl_from_bridge_kind_ref_mut!(BridgePart);

#[macro_export]
macro_rules! impl_try_from_bridge_kind_ref_mut {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::bridge::refs::AbstractBridgeKindRefMut<'a>>
            for &'a mut $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::bridge::refs::AbstractBridgeKindRefMut<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::bridge::refs::AbstractBridgeKindRefMut::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind_ref_mut!(AbstractBridgeKind, $type);
    };
}
impl_try_from_bridge_kind_ref_mut!(Bridge);
impl_try_from_bridge_kind_ref_mut!(BridgePart);
impl_try_from_construction_kind_ref_mut_for_enum!(AbstractBridgeKind, AbstractBridgeKindRefMut);

impl<'a> RecomputeBoundingShape for AbstractBridgeKindRefMut<'a> {
    fn recompute_bounding_shape(&mut self) {
        match self {
            Self::Bridge(x) => x.recompute_bounding_shape(),
            Self::BridgePart(x) => x.recompute_bounding_shape(),
        }
    }
}
