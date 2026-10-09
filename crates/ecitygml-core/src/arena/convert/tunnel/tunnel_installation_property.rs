use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::tunnel::tunnel_installation::flatten_tunnel_installation;
use crate::model::common::arena::HasArenaPropertiesMut;
use crate::model::tunnel::TunnelInstallationProperty;

pub fn flatten_tunnel_installation_property(
    tunnel_installation_property: &mut TunnelInstallationProperty,
    city_model_arena: &mut CityModelArena,
) {
    let Some(object) = tunnel_installation_property.take_object() else {
        return;
    };

    let internal_key = flatten_tunnel_installation(object, city_model_arena);
    tunnel_installation_property.set_key(internal_key);
}
