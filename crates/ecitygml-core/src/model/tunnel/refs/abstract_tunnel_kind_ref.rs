use crate::impl_try_from_construction_kind_ref_for_enum;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::tunnel::{
    AbstractTunnel, AbstractTunnelKind, AsAbstractTunnel, Tunnel, TunnelPart,
};

#[derive(Debug, Clone, Copy)]
pub enum AbstractTunnelKindRef<'a> {
    Tunnel(&'a Tunnel),
    TunnelPart(&'a TunnelPart),
}

impl<'a> From<&'a AbstractTunnelKind> for AbstractTunnelKindRef<'a> {
    fn from(item: &'a AbstractTunnelKind) -> Self {
        match item {
            AbstractTunnelKind::Tunnel(x) => Self::Tunnel(x),
            AbstractTunnelKind::TunnelPart(x) => Self::TunnelPart(x),
        }
    }
}

impl<'a> AsAbstractTunnel for AbstractTunnelKindRef<'a> {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        match self {
            Self::Tunnel(x) => x.abstract_tunnel(),
            Self::TunnelPart(x) => x.abstract_tunnel(),
        }
    }
}
crate::impl_abstract_tunnel_traits!(AbstractTunnelKindRef<'_>);

impl<'a> HasFeatureType for AbstractTunnelKindRef<'a> {
    fn feature_type(&self) -> FeatureType {
        match *self {
            Self::Tunnel(_) => FeatureType::Tunnel,
            Self::TunnelPart(_) => FeatureType::TunnelPart,
        }
    }
}

#[macro_export]
macro_rules! impl_from_tunnel_kind_ref {
    ($type:ident) => {
        impl<'a> From<&'a $type> for $crate::model::tunnel::refs::AbstractTunnelKindRef<'a> {
            fn from(x: &'a $type) -> Self {
                $crate::model::tunnel::refs::AbstractTunnelKindRef::$type(x.into())
            }
        }
        $crate::impl_from_for_construction_kind_ref!(AbstractTunnelKind, $type);
    };
}
impl_from_tunnel_kind_ref!(Tunnel);
impl_from_tunnel_kind_ref!(TunnelPart);

#[macro_export]
macro_rules! impl_try_from_tunnel_kind_ref {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::tunnel::refs::AbstractTunnelKindRef<'a>> for &'a $type {
            type Error = ();
            fn try_from(
                x: $crate::model::tunnel::refs::AbstractTunnelKindRef<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::tunnel::refs::AbstractTunnelKindRef::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind_ref!(AbstractTunnelKind, $type);
    };
}
impl_try_from_tunnel_kind_ref!(Tunnel);
impl_try_from_tunnel_kind_ref!(TunnelPart);
impl_try_from_construction_kind_ref_for_enum!(AbstractTunnelKind, AbstractTunnelKindRef);
