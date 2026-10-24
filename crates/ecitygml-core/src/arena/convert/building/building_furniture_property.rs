use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::building::building_furniture::flatten_building_furniture;
use crate::model::building::BuildingFurnitureProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_building_furniture_property(
    building_furniture_property: &mut BuildingFurnitureProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = building_furniture_property.take_object() else {
        return;
    };

    let internal_key = flatten_building_furniture(object, city_model_arena);
    building_furniture_property.set_key(internal_key);
}
