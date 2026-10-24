//! The cases of `arena.md`.

use crate::{fixture, read};
use ecitygml::arena::CityModelArena;
use egml::model::base::Id;
use egml::model::feature::AsAbstractFeature;

#[test]
fn arena_lookup() {
    let city_model = read(&fixture(
        "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
    ));
    let arena = CityModelArena::from_city_model(city_model).expect("should index the city model");
    assert_eq!(arena.iter_city_objects().count(), 8);
    let id: Id = "GML_5856d7ad-5e34-498a-817b-9544bfbb1475"
        .try_into()
        .expect("should be an id");
    let wall = arena
        .get_city_object_by_id(&id)
        .expect("should find the wall surface");
    assert!(
        wall.bounded_by()
            .and_then(|shape| shape.envelope())
            .is_some()
    );
}
