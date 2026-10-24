use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_furniture;
use crate::model::common::arena::InternalKey;
use crate::model::construction::AsAbstractFurnitureMut;
use crate::model::tunnel::TunnelFurniture;

pub fn flatten_tunnel_furniture(
    mut tunnel_furniture: TunnelFurniture,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_furniture(tunnel_furniture.abstract_furniture_mut(), city_model_arena);

    city_model_arena
        .insert_feature(tunnel_furniture.into())
        .into()
}
