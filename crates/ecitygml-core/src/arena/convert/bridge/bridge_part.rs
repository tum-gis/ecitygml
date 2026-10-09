use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::abstract_bridge::flatten_abstract_bridge;
use crate::model::bridge::AsAbstractBridgeMut;
use crate::model::bridge::BridgePart;
use crate::model::common::arena::InternalKey;

pub fn flatten_bridge_part(
    mut bridge_part: BridgePart,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_bridge(bridge_part.abstract_bridge_mut(), city_model_arena);

    city_model_arena.insert_feature(bridge_part.into()).into()
}
