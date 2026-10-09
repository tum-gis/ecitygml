use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_part::flatten_bridge_part;
use crate::model::bridge::BridgePartProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_bridge_part_property(
    bridge_part_property: &mut BridgePartProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = bridge_part_property.take_object() else {
        return;
    };

    let internal_key = flatten_bridge_part(object, city_model_arena);
    bridge_part_property.set_key(internal_key);
}
