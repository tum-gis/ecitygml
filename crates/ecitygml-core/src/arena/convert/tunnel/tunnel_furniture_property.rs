use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::tunnel_furniture::flatten_tunnel_furniture;
use crate::model::common::arena::HasArenaPropertiesMut;
use crate::model::tunnel::TunnelFurnitureProperty;

pub fn flatten_tunnel_furniture_property(
    tunnel_furniture_property: &mut TunnelFurnitureProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = tunnel_furniture_property.take_object() else {
        return;
    };

    let internal_key = flatten_tunnel_furniture(object, city_model_arena);
    tunnel_furniture_property.set_key(internal_key);
}
