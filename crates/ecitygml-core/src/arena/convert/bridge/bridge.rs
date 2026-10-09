use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::abstract_bridge::flatten_abstract_bridge;
use crate::arena::convert::bridge::bridge_part_property::flatten_bridge_part_property;
use crate::model::bridge::AsAbstractBridgeMut;
use crate::model::bridge::Bridge;
use crate::model::common::arena::InternalKey;

pub fn flatten_bridge(mut bridge: Bridge, city_model_arena: &mut CityModelArena) -> InternalKey {
    flatten_abstract_bridge(bridge.abstract_bridge_mut(), city_model_arena);

    for prop in bridge.bridge_parts_mut() {
        flatten_bridge_part_property(prop, city_model_arena);
    }

    city_model_arena.insert_feature(bridge.into()).into()
}
