use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_construction;
use crate::arena::convert::tunnel::tunnel_constructive_element_property::flatten_tunnel_constructive_element_property;
use crate::arena::convert::tunnel::tunnel_installation_property::flatten_tunnel_installation_property;
use crate::model::construction::AsAbstractConstructionMut;
use crate::model::tunnel::{AbstractTunnel, AsAbstractTunnelMut};

pub fn flatten_abstract_tunnel(
    abstract_tunnel: &mut AbstractTunnel,
    city_model_arena: &mut CityModelArena,
) {
    flatten_abstract_construction(
        abstract_tunnel.abstract_construction_mut(),
        city_model_arena,
    );

    for prop in abstract_tunnel.tunnel_installations_mut() {
        flatten_tunnel_installation_property(prop, city_model_arena);
    }
    for prop in abstract_tunnel.tunnel_constructive_elements_mut() {
        flatten_tunnel_constructive_element_property(prop, city_model_arena);
    }
}
