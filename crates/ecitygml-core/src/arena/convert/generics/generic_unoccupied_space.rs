use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::core::flatten_abstract_unoccupied_space;
use crate::model::common::arena::InternalKey;
use crate::model::core::AsAbstractUnoccupiedSpaceMut;
use crate::model::generics::GenericUnoccupiedSpace;

pub fn flatten_generic_unoccupied_space(
    mut generic_unoccupied_space: GenericUnoccupiedSpace,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_unoccupied_space(
        generic_unoccupied_space.abstract_unoccupied_space_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(generic_unoccupied_space.into())
        .into()
}
