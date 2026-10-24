use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::core::flatten_abstract_logical_space;
use crate::model::common::arena::InternalKey;
use crate::model::core::AsAbstractLogicalSpaceMut;
use crate::model::generics::GenericLogicalSpace;

pub fn flatten_generic_logical_space(
    mut generic_logical_space: GenericLogicalSpace,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_logical_space(
        generic_logical_space.abstract_logical_space_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(generic_logical_space.into())
        .into()
}
