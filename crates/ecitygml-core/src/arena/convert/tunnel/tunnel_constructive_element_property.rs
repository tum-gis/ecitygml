use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::tunnel_constructive_element::flatten_tunnel_constructive_element;
use crate::model::common::arena::HasArenaPropertiesMut;
use crate::model::tunnel::TunnelConstructiveElementProperty;

pub fn flatten_tunnel_constructive_element_property(
    tunnel_constructive_element_property: &mut TunnelConstructiveElementProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = tunnel_constructive_element_property.take_object() else {
        return;
    };

    let internal_key = flatten_tunnel_constructive_element(object, city_model_arena);
    tunnel_constructive_element_property.set_key(internal_key);
}
