use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_room::flatten_bridge_room;
use crate::model::bridge::BridgeRoomProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_bridge_room_property(
    bridge_room_property: &mut BridgeRoomProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = bridge_room_property.take_object() else {
        return;
    };

    let internal_key = flatten_bridge_room(object, city_model_arena);
    bridge_room_property.set_key(internal_key);
}
