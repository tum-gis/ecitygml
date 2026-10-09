use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::bridge::bridge_installation::flatten_bridge_installation;
use crate::model::bridge::BridgeInstallationProperty;
use crate::model::common::arena::HasArenaPropertiesMut;

pub fn flatten_bridge_installation_property(
    bridge_installation_property: &mut BridgeInstallationProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = bridge_installation_property.take_object() else {
        return;
    };

    let internal_key = flatten_bridge_installation(object, city_model_arena);
    bridge_installation_property.set_key(internal_key);
}
