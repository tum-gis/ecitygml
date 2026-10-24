use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::core::flatten_abstract_occupied_space;
use crate::model::construction::AbstractFurniture;
use crate::model::core::AsAbstractOccupiedSpaceMut;

pub fn flatten_abstract_furniture(
    abstract_furniture: &mut AbstractFurniture,
    city_model_arena: &mut CityModelArena,
) {
    flatten_abstract_occupied_space(
        abstract_furniture.abstract_occupied_space_mut(),
        city_model_arena,
    )
}
