use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::hollow_space::flatten_hollow_space;
use crate::model::common::arena::HasArenaPropertiesMut;
use crate::model::tunnel::HollowSpaceProperty;

pub fn flatten_hollow_space_property(
    hollow_space_property: &mut HollowSpaceProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = hollow_space_property.take_object() else {
        return;
    };

    let internal_key = flatten_hollow_space(object, city_model_arena);
    hollow_space_property.set_key(internal_key);
}
