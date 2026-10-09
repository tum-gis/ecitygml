use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_constructive_element;
use crate::model::bridge::BridgeConstructiveElement;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractConstructiveElementMut;

pub fn flatten_bridge_constructive_element(
    mut bridge_constructive_element: BridgeConstructiveElement,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_constructive_element(
        bridge_constructive_element.abstract_constructive_element_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(bridge_constructive_element.into())
        .into()
}
