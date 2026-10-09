use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::tunnel_part::flatten_tunnel_part;
use crate::model::common::arena::HasArenaPropertiesMut;
use crate::model::tunnel::TunnelPartProperty;

pub fn flatten_tunnel_part_property(
    tunnel_part_property: &mut TunnelPartProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = tunnel_part_property.take_object() else {
        return;
    };

    let internal_key = flatten_tunnel_part(object, city_model_arena);
    tunnel_part_property.set_key(internal_key);
}
