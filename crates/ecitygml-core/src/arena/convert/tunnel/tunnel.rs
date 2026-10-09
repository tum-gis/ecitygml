use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::abstract_tunnel::flatten_abstract_tunnel;
use crate::arena::convert::tunnel::tunnel_part_property::flatten_tunnel_part_property;
use crate::model::common::arena::InternalKey;
use crate::model::tunnel::AsAbstractTunnelMut;
use crate::model::tunnel::Tunnel;

pub fn flatten_tunnel(mut tunnel: Tunnel, city_model_arena: &mut CityModelArena) -> InternalKey {
    flatten_abstract_tunnel(tunnel.abstract_tunnel_mut(), city_model_arena);

    for prop in tunnel.tunnel_parts_mut() {
        flatten_tunnel_part_property(prop, city_model_arena);
    }

    city_model_arena.insert_feature(tunnel.into()).into()
}
