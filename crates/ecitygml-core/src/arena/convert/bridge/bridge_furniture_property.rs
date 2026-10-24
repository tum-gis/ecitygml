use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_furniture::flatten_bridge_furniture;
use crate::model::bridge::BridgeFurnitureProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_bridge_furniture_property(
    bridge_furniture_property: &mut BridgeFurnitureProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = bridge_furniture_property.take_object() else {
        return;
    };

    let internal_key = flatten_bridge_furniture(object, city_model_arena);
    bridge_furniture_property.set_key(internal_key);
}
