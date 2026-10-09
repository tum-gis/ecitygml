use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::core::flatten_abstract_logical_space;
use crate::model::city_object_group::CityObjectGroup;
use crate::model::common::arena::InternalKey;
use crate::model::core::AsAbstractLogicalSpaceMut;

pub fn flatten_city_object_group(
    mut city_object_group: CityObjectGroup,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_logical_space(
        city_object_group.abstract_logical_space_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(city_object_group.into())
        .into()
}
