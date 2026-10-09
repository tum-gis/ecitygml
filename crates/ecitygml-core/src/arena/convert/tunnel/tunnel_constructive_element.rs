use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_constructive_element;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractConstructiveElementMut;
use crate::model::tunnel::TunnelConstructiveElement;

pub fn flatten_tunnel_constructive_element(
    mut tunnel_constructive_element: TunnelConstructiveElement,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_constructive_element(
        tunnel_constructive_element.abstract_constructive_element_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(tunnel_constructive_element.into())
        .into()
}
