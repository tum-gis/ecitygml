use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_furniture_property::flatten_bridge_furniture_property;
use crate::arena::convert::core::flatten_abstract_unoccupied_space;
use crate::model::bridge::BridgeRoom;
use crate::model::common::arena::InternalKey;
use crate::model::core::AsAbstractUnoccupiedSpaceMut;

pub fn flatten_bridge_room(
    mut bridge_room: BridgeRoom,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_unoccupied_space(
        bridge_room.abstract_unoccupied_space_mut(),
        city_model_arena,
    );
    for prop in bridge_room.bridge_furniture_mut() {
        flatten_bridge_furniture_property(prop, city_model_arena);
    }

    city_model_arena.insert_feature(bridge_room.into()).into()
}
