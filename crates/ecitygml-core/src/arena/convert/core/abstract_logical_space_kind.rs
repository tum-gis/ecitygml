use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::building::flatten_abstract_building_subdivision_kind;
use crate::arena::convert::city_object_group::flatten_city_object_group;
use crate::arena::convert::generics::flatten_generic_logical_space;
use crate::model::common::arena::InternalKey;
use crate::model::core::AbstractLogicalSpaceKind;

pub fn flatten_abstract_logical_space_kind(
    abstract_logical_space_kind: AbstractLogicalSpaceKind,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    match abstract_logical_space_kind {
        AbstractLogicalSpaceKind::AbstractBuildingSubdivisionKind(x) => {
            flatten_abstract_building_subdivision_kind(x, city_model_arena)
        }
        AbstractLogicalSpaceKind::CityObjectGroup(x) => {
            flatten_city_object_group(x, city_model_arena)
        }
        AbstractLogicalSpaceKind::GenericLogicalSpace(x) => {
            flatten_generic_logical_space(x, city_model_arena)
        }
    }
}
