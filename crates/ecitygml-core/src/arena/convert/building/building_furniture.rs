use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_furniture;
use crate::model::building::BuildingFurniture;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractFurnitureMut;

pub fn flatten_building_furniture(
    mut building_furniture: BuildingFurniture,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_furniture(
        building_furniture.abstract_furniture_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(building_furniture.into())
        .into()
}
