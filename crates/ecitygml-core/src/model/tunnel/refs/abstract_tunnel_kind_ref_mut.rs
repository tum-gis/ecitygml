use crate::impl_try_from_construction_kind_ref_mut_for_enum;
use crate::model::common::FeatureType;
use crate::model::common::HasFeatureType;
use crate::model::tunnel::{
    AbstractTunnel, AbstractTunnelKind, AsAbstractTunnel, AsAbstractTunnelMut, Tunnel, TunnelPart,
};
use egml::model::common::RecomputeBoundingShape;

#[derive(Debug)]
pub enum AbstractTunnelKindRefMut<'a> {
    Tunnel(&'a mut Tunnel),
    TunnelPart(&'a mut TunnelPart),
}

impl<'a> From<&'a mut AbstractTunnelKind> for AbstractTunnelKindRefMut<'a> {
    fn from(item: &'a mut AbstractTunnelKind) -> Self {
        match item {
            AbstractTunnelKind::Tunnel(x) => Self::Tunnel(x),
            AbstractTunnelKind::TunnelPart(x) => Self::TunnelPart(x),
        }
    }
}

impl<'a> AsAbstractTunnel for AbstractTunnelKindRefMut<'a> {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        match self {
            Self::Tunnel(x) => x.abstract_tunnel(),
            Self::TunnelPart(x) => x.abstract_tunnel(),
        }
    }
}

impl<'a> AsAbstractTunnelMut for AbstractTunnelKindRefMut<'a> {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel {
        match self {
            Self::Tunnel(x) => x.abstract_tunnel_mut(),
            Self::TunnelPart(x) => x.abstract_tunnel_mut(),
        }
    }
}
crate::impl_abstract_tunnel_traits!(AbstractTunnelKindRefMut<'_>);
crate::impl_abstract_tunnel_mut_traits!(AbstractTunnelKindRefMut<'_>);

impl<'a> HasFeatureType for AbstractTunnelKindRefMut<'a> {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::Tunnel(x) => x.feature_type(),
            Self::TunnelPart(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_tunnel_kind_ref_mut {
    ($type:ident) => {
        impl<'a> From<&'a mut $type> for $crate::model::tunnel::refs::AbstractTunnelKindRefMut<'a> {
            fn from(x: &'a mut $type) -> Self {
                $crate::model::tunnel::refs::AbstractTunnelKindRefMut::$type(x.into())
            }
        }
        $crate::impl_from_for_construction_kind_ref_mut!(AbstractTunnelKind, $type);
    };
}
impl_from_tunnel_kind_ref_mut!(Tunnel);
impl_from_tunnel_kind_ref_mut!(TunnelPart);

#[macro_export]
macro_rules! impl_try_from_tunnel_kind_ref_mut {
    ($type:ident) => {
        impl<'a> TryFrom<$crate::model::tunnel::refs::AbstractTunnelKindRefMut<'a>>
            for &'a mut $type
        {
            type Error = ();
            fn try_from(
                x: $crate::model::tunnel::refs::AbstractTunnelKindRefMut<'a>,
            ) -> Result<Self, ()> {
                match x {
                    $crate::model::tunnel::refs::AbstractTunnelKindRefMut::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind_ref_mut!(AbstractTunnelKind, $type);
    };
}
impl_try_from_tunnel_kind_ref_mut!(Tunnel);
impl_try_from_tunnel_kind_ref_mut!(TunnelPart);
impl_try_from_construction_kind_ref_mut_for_enum!(AbstractTunnelKind, AbstractTunnelKindRefMut);

impl<'a> RecomputeBoundingShape for AbstractTunnelKindRefMut<'a> {
    fn recompute_bounding_shape(&mut self) {
        match self {
            Self::Tunnel(x) => x.recompute_bounding_shape(),
            Self::TunnelPart(x) => x.recompute_bounding_shape(),
        }
    }
}
