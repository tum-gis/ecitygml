use crate::impl_try_from_construction_kind_ref_for_enum;
use crate::model::bridge::{
    AbstractBridge, AbstractBridgeKind, AsAbstractBridge, Bridge, BridgePart,
};
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;

#[derive(Debug, Clone, Copy)]
pub enum AbstractBridgeKindRef<'a> {
    Bridge(&'a Bridge),
    BridgePart(&'a BridgePart),
}

impl<'a> From<&'a AbstractBridgeKind> for AbstractBridgeKindRef<'a> {
    fn from(item: &'a AbstractBridgeKind) -> Self {
        match item {
            AbstractBridgeKind::Bridge(x) => Self::Bridge(x),
            AbstractBridgeKind::BridgePart(x) => Self::BridgePart(x),
        }
    }
}

impl<'a> AsAbstractBridge for AbstractBridgeKindRef<'a> {
    fn abstract_bridge(&self) -> &AbstractBridge {
        match self {
            Self::Bridge(x) => x.abstract_bridge(),
            Self::BridgePart(x) => x.abstract_bridge(),
        }
    }
}
crate::impl_abstract_bridge_traits!(AbstractBridgeKindRef<'_>);

impl<'a> HasFeatureType for AbstractBridgeKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::Bridge(_) => FeatureType::Bridge,
            Self::BridgePart(_) => FeatureType::BridgePart,
        }
    }
}

#[macro_export]
macro_rules! impl_from_bridge_kind_ref {
    ($type:ident) => {
        impl<'a> From<&'a $type> for $crate::model::bridge::refs::AbstractBridgeKindRef<'a> {
            fn from(x: &'a $type) -> Self {
                $crate::model::bridge::refs::AbstractBridgeKindRef::$type(x.into())
            }
        }
        $crate::impl_from_for_construction_kind_ref!(AbstractBridgeKind, $type);
    };
}
impl_from_bridge_kind_ref!(Bridge);
impl_from_bridge_kind_ref!(BridgePart);

#[macro_export]
macro_rules! impl_try_from_bridge_kind_ref {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::bridge::refs::AbstractBridgeKindRef<'a>> for &'a $type {
            type Error = ();
            fn try_from(
                x: $crate::model::bridge::refs::AbstractBridgeKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::bridge::refs::AbstractBridgeKindRef::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind_ref!(AbstractBridgeKind, $type);
    };
}
impl_try_from_bridge_kind_ref!(Bridge);
impl_try_from_bridge_kind_ref!(BridgePart);
impl_try_from_construction_kind_ref_for_enum!(AbstractBridgeKind, AbstractBridgeKindRef);
