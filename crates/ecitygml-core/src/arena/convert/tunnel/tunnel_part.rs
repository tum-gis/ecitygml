use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::abstract_tunnel::flatten_abstract_tunnel;
use crate::model::common::arena::InternalKey;
use crate::model::tunnel::AsAbstractTunnelMut;
use crate::model::tunnel::TunnelPart;

pub fn flatten_tunnel_part(
    mut tunnel_part: TunnelPart,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_tunnel(tunnel_part.abstract_tunnel_mut(), city_model_arena);

    city_model_arena.insert_feature(tunnel_part.into()).into()
}
