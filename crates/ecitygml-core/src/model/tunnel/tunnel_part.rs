use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::tunnel::{AbstractTunnel, AsAbstractTunnel, AsAbstractTunnelMut};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct TunnelPart {
    pub(crate) abstract_tunnel: AbstractTunnel,
}

impl TunnelPart {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_tunnel(AbstractTunnel::new(id))
    }

    pub fn from_abstract_tunnel(abstract_tunnel: AbstractTunnel) -> Self {
        Self { abstract_tunnel }
    }
}

impl AsAbstractTunnel for TunnelPart {
    fn abstract_tunnel(&self) -> &AbstractTunnel {
        &self.abstract_tunnel
    }
}

impl AsAbstractTunnelMut for TunnelPart {
    fn abstract_tunnel_mut(&mut self) -> &mut AbstractTunnel {
        &mut self.abstract_tunnel
    }
}

crate::impl_abstract_tunnel_traits!(TunnelPart);
crate::impl_abstract_tunnel_mut_traits!(TunnelPart);
crate::impl_has_feature_type!(TunnelPart, TunnelPart);

impl IterFeatures for TunnelPart {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        Box::new(std::iter::once(self.into()).chain(self.abstract_tunnel.iter_features()))
    }
}

impl ForEachFeatureMut for TunnelPart {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        f((&mut *self).into());
        self.abstract_tunnel.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for TunnelPart {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_tunnel.compute_envelope()
    }
}

impl ApplyTransform for TunnelPart {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_tunnel.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_tunnel.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_tunnel.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_tunnel.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_tunnel.apply_scale(scale);
    }
}
