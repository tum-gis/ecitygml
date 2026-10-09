use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::tunnel::flatten_tunnel;
use crate::arena::convert::tunnel::tunnel_part::flatten_tunnel_part;
use crate::model::common::arena::InternalKey;
use crate::model::tunnel::AbstractTunnelKind;

pub fn flatten_abstract_tunnel_kind(
    abstract_tunnel_kind: AbstractTunnelKind,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    match abstract_tunnel_kind {
        AbstractTunnelKind::Tunnel(x) => flatten_tunnel(x, city_model_arena),
        AbstractTunnelKind::TunnelPart(x) => flatten_tunnel_part(x, city_model_arena),
    }
}
