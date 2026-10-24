use crate::arena::city_model_arena::CityModelArena;
use crate::arena::convert::construction::flatten_abstract_construction;
use crate::model::common::arena::InternalKey;
use crate::model::construction::{AsAbstractConstructionMut, OtherConstruction};

pub fn flatten_other_construction(
    mut other_construction: OtherConstruction,
    city_model_arena: &mut CityModelArena,
) -> InternalKey {
    flatten_abstract_construction(
        other_construction.abstract_construction_mut(),
        city_model_arena,
    );

    city_model_arena
        .insert_feature(other_construction.into())
        .into()
}
