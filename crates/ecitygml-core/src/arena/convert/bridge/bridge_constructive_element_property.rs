use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_constructive_element::flatten_bridge_constructive_element;
use crate::model::bridge::BridgeConstructiveElementProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_bridge_constructive_element_property(
    bridge_constructive_element_property: &mut BridgeConstructiveElementProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = bridge_constructive_element_property.take_object() else {
        return;
    };

    let internal_key = flatten_bridge_constructive_element(object, city_model_arena);
    bridge_constructive_element_property.set_key(internal_key);
}
