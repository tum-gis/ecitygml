use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_installation;
use crate::model::bridge::BridgeInstallation;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractInstallationMut;

pub fn flatten_bridge_installation(
    mut bridge_installation: BridgeInstallation,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_installation(
        bridge_installation.abstract_installation_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(bridge_installation.into())
        .into()
}
