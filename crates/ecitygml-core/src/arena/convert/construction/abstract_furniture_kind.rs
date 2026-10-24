use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::flatten_bridge_furniture;
use crate::arena::convert::building::flatten_building_furniture;
use crate::arena::convert::tunnel::flatten_tunnel_furniture;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AbstractFurnitureKind;

pub fn flatten_abstract_furniture_kind(
    abstract_furniture_kind: AbstractFurnitureKind,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    match abstract_furniture_kind {
        AbstractFurnitureKind::BridgeFurniture(x) => flatten_bridge_furniture(x, city_model_arena),
        AbstractFurnitureKind::BuildingFurniture(x) => {
            flatten_building_furniture(x, city_model_arena)
        }
        AbstractFurnitureKind::TunnelFurniture(x) => flatten_tunnel_furniture(x, city_model_arena),
    }
}
