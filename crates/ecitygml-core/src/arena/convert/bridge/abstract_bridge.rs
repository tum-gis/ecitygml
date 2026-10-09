use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_constructive_element_property::flatten_bridge_constructive_element_property;
use crate::arena::convert::bridge::bridge_installation_property::flatten_bridge_installation_property;
use crate::arena::convert::construction::flatten_abstract_construction;
use crate::model::bridge::{AbstractBridge, AsAbstractBridgeMut};
use crate::model::construction::AsAbstractConstructionMut;

pub fn flatten_abstract_bridge(
    abstract_bridge: &mut AbstractBridge,
    city_model_arena: &mut CityModelArena,
) {
    flatten_abstract_construction(
        abstract_bridge.abstract_construction_mut(),
        city_model_arena,
    );

    for prop in abstract_bridge.bridge_installations_mut() {
        flatten_bridge_installation_property(prop, city_model_arena);
    }
    for prop in abstract_bridge.bridge_constructive_elements_mut() {
        flatten_bridge_constructive_element_property(prop, city_model_arena);
    }
}
