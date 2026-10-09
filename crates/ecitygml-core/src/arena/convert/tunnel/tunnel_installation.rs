use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_installation;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractInstallationMut;
use crate::model::tunnel::TunnelInstallation;

pub fn flatten_tunnel_installation(
    mut tunnel_installation: TunnelInstallation,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_installation(
        tunnel_installation.abstract_installation_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(tunnel_installation.into())
        .into()
}
