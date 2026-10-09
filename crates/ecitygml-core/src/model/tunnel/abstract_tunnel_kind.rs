use crate::impl_abstract_tunnel_mut_traits;
use crate::impl_abstract_tunnel_traits;
use crate::model::common::{FeatureType, ForEachFeatureMut, HasFeatureType, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::{
    AbstractTunnel, AsAbstractTunnel, AsAbstractTunnelMut, Tunnel, TunnelPart,
};
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub enum AbstractTunnelKind {
    Tunnel(Tunnel),
    TunnelPart(TunnelPart),
}

impl AsAbstractTunnel for AbstractTunnelKind {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.abstract_tunnel(),
            AbstractTunnelKind::TunnelPart(x) => x.abstract_tunnel(),
        }
    }
}

impl AsAbstractTunnelMut for AbstractTunnelKind {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.abstract_tunnel_mut(),
            AbstractTunnelKind::TunnelPart(x) => x.abstract_tunnel_mut(),
        }
    }
}

impl_abstract_tunnel_traits!(AbstractTunnelKind);
impl_abstract_tunnel_mut_traits!(AbstractTunnelKind);

impl HasFeatureType for AbstractTunnelKind {
    fn feature_type(&self) -> FeatureType {
        match self {
            Self::Tunnel(x) => x.feature_type(),
            Self::TunnelPart(x) => x.feature_type(),
        }
    }
}

#[macro_export]
macro_rules! impl_from_tunnel_kind {
    ($type:ident) => {
        impl From<$type> for $crate::model::tunnel::AbstractTunnelKind {
            fn from(x: $type) -> Self {
                $crate::model::tunnel::AbstractTunnelKind::$type(x)
            }
        }
        $crate::impl_from_for_construction_kind!(AbstractTunnelKind, $type);
    };
}
impl_from_tunnel_kind!(Tunnel);
impl_from_tunnel_kind!(TunnelPart);

#[macro_export]
macro_rules! impl_try_from_tunnel_kind {
    ($type:ident) => {
        impl TryFrom<$crate::model::tunnel::AbstractTunnelKind> for $type {
            type Error = ();
            fn try_from(x: $crate::model::tunnel::AbstractTunnelKind) -> Result<Self, ()> {
                match x {
                    $crate::model::tunnel::AbstractTunnelKind::$type(k) => {
                        k.try_into().map_err(|_| ())
                    }
                    #[allow(unreachable_patterns)]
                    _ => Err(()),
                }
            }
        }
        $crate::impl_try_from_for_construction_kind!(AbstractTunnelKind, $type);
    };
}
impl_try_from_tunnel_kind!(Tunnel);
impl_try_from_tunnel_kind!(TunnelPart);

impl IterFeatures for AbstractTunnelKind {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.iter_features(),
            AbstractTunnelKind::TunnelPart(x) => x.iter_features(),
        }
    }
}

impl ForEachFeatureMut for AbstractTunnelKind {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.for_each_feature_mut(f),
            AbstractTunnelKind::TunnelPart(x) => x.for_each_feature_mut(f),
        }
    }
}

impl ComputeEnvelope for AbstractTunnelKind {
    fn compute_envelope(&self) -> Option<Envelope> {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.compute_envelope(),
            AbstractTunnelKind::TunnelPart(x) => x.compute_envelope(),
        }
    }
}

impl ApplyTransform for AbstractTunnelKind {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.apply_transform(m),
            AbstractTunnelKind::TunnelPart(x) => x.apply_transform(m),
        }
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.apply_isometry(isometry),
            AbstractTunnelKind::TunnelPart(x) => x.apply_isometry(isometry),
        }
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.apply_translation(vector),
            AbstractTunnelKind::TunnelPart(x) => x.apply_translation(vector),
        }
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.apply_rotation(rotation),
            AbstractTunnelKind::TunnelPart(x) => x.apply_rotation(rotation),
        }
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        match self {
            AbstractTunnelKind::Tunnel(x) => x.apply_scale(scale),
            AbstractTunnelKind::TunnelPart(x) => x.apply_scale(scale),
        }
    }
}
