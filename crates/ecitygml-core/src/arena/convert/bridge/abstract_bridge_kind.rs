use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge::flatten_bridge;
use crate::arena::convert::bridge::bridge_part::flatten_bridge_part;
use crate::model::bridge::AbstractBridgeKind;
use crate::model::common::arena::InternalKey;

pub fn flatten_abstract_bridge_kind(
    abstract_bridge_kind: AbstractBridgeKind,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    match abstract_bridge_kind {
        AbstractBridgeKind::Bridge(x) => flatten_bridge(x, city_model_arena),
        AbstractBridgeKind::BridgePart(x) => flatten_bridge_part(x, city_model_arena),
    }
}
