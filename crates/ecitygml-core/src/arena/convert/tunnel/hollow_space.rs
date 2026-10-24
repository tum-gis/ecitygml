use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::core::flatten_abstract_unoccupied_space;
use crate::arena::convert::tunnel::tunnel_furniture_property::flatten_tunnel_furniture_property;
use crate::model::common::arena::InternalKey;
use crate::model::core::AsAbstractUnoccupiedSpaceMut;
use crate::model::tunnel::HollowSpace;

pub fn flatten_hollow_space(
    mut hollow_space: HollowSpace,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_unoccupied_space(
        hollow_space.abstract_unoccupied_space_mut(),
        city_model_arena,
    );
    for prop in hollow_space.tunnel_furniture_mut() {
        flatten_tunnel_furniture_property(prop, city_model_arena);
    }

    city_model_arena.insert_feature(hollow_space.into()).into()
}
