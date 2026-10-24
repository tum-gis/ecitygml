use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_furniture;
use crate::model::bridge::BridgeFurniture;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractFurnitureMut;

pub fn flatten_bridge_furniture(
    mut bridge_furniture: BridgeFurniture,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_furniture(bridge_furniture.abstract_furniture_mut(), city_model_arena);

    city_model_arena
        .insert_feature(bridge_furniture.into())
        .into()
}
