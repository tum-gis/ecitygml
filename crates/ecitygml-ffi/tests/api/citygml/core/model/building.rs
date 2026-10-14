//! `Building`, `BuildingPart` and `Height`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::building::building_part::BuildingPart;
use ecitygml_ffi::citygml::core::model::construction::enums::height_status_value::HeightStatusValue;

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Building::try_from(&feature))
        .unwrap()
}

#[test]
fn own_and_inherited_getters() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let building = first_building(&city_model);

    // AbstractBuilding
    assert_eq!(building.class().unwrap().value(), "1000");
    let mut functions = building.functions();
    assert_eq!(functions.next().unwrap().value(), "1000");
    assert!(functions.next().is_none());
    assert_eq!(building.usages().next().unwrap().code().value(), "1000");
    assert_eq!(building.roof_type().unwrap().value(), "1030");
    assert_eq!(building.storeys_above_ground(), Some(2));
    assert_eq!(building.storeys_below_ground(), Some(0));

    // AbstractConstruction
    let date = building.date_of_construction().unwrap();
    assert_eq!((date.year(), date.month(), date.day()), (2020, 1, 1));
    assert!(building.date_of_demolition().is_none());
    let mut heights = building.heights();
    let height = heights.next().unwrap();
    assert!(heights.next().is_none());
    assert_eq!(height.high_reference().value(), "topOfConstruction");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_eq!(height.length().value(), 6.52);
    assert_eq!(height.length().uom(), "m");
    assert!(building.occupancies().next().is_none());

    // AbstractSpace, AbstractFeature
    let solid = building.lod1_solid().unwrap().object().unwrap();
    assert!((solid.volume_3d().unwrap() - 782.1228).abs() < 1e-6);
    assert_eq!(
        building.feature_id().as_str(),
        "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
    );

    // Building
    assert!(building.building_parts().next().is_none());
}

#[test]
fn building_part() {
    let city_model = read_modified(
        "</bldg:Building>",
        "<bldg:buildingPart><bldg:BuildingPart gml:id=\"BP_1\"><bldg:roofType>1000</bldg:roofType><bldg:storeysAboveGround>1</bldg:storeysAboveGround></bldg:BuildingPart></bldg:buildingPart></bldg:Building>",
    );
    let building = first_building(&city_model);
    let mut parts = building.building_parts();
    let property = parts.next().unwrap();
    assert!(parts.next().is_none());
    assert!(property.href().is_none());
    let part = property.object().unwrap();
    assert_eq!(part.feature_id().as_str(), "BP_1");
    assert_eq!(part.roof_type().unwrap().value(), "1000");
    assert_eq!(part.storeys_above_ground(), Some(1));
    assert!(part.class().is_none());

    // Found via iter_features, and not a building.
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    let parts: Vec<_> = features
        .iter()
        .filter_map(|f| BuildingPart::try_from(f))
        .collect();
    assert_eq!(parts.len(), 1);
    assert_eq!(
        features
            .iter()
            .filter_map(|f| Building::try_from(f))
            .count(),
        1
    );
}

mod subdivisions {
    use super::*;
    use ecitygml_ffi::citygml::core::model::building::building_unit::BuildingUnit;
    use ecitygml_ffi::citygml::core::model::building::storey::Storey;
    use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;

    // No fixture contains building subdivisions; they are injected into a copy of the FZK LoD2
    // building after its storey counts, as in the CityGML 3.0 schema (AbstractBuildingType).
    const ANCHOR: &str = "<bldg:storeysBelowGround>0</bldg:storeysBelowGround>";
    const SUBDIVISIONS: &str = r#"<bldg:storeysBelowGround>0</bldg:storeysBelowGround>
      <bldg:buildingSubdivision>
        <bldg:Storey gml:id="storey_ground">
          <bldg:class codeSpace="https://example.org/storey_class">ground</bldg:class>
          <bldg:function>living</bldg:function>
        </bldg:Storey>
      </bldg:buildingSubdivision>
      <bldg:buildingSubdivision>
        <bldg:BuildingUnit gml:id="unit_1">
          <bldg:usage>residential</bldg:usage>
        </bldg:BuildingUnit>
      </bldg:buildingSubdivision>"#;

    #[test]
    fn storey_and_building_unit() {
        let city_model = read_fixture_modified(
            "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
            ANCHOR,
            SUBDIVISIONS,
        );
        let building = first_building(&city_model);
        let mut subdivisions = building.building_subdivisions();
        let storey = subdivisions.next().unwrap();
        let unit = subdivisions.next().unwrap();
        assert!(subdivisions.next().is_none());
        assert!(storey.href().is_none());
        let (storey, unit) = (storey.object().unwrap(), unit.object().unwrap());

        // AbstractBuildingSubdivisionKind: feature type and the getters of every ancestor.
        assert_eq!(storey.feature_type(), FeatureType::Storey);
        assert_eq!(unit.feature_type(), FeatureType::BuildingUnit);
        assert_eq!(storey.feature_id().as_str(), "storey_ground");
        let class = storey.class().unwrap().code();
        assert_eq!(
            (class.value(), class.code_space()),
            ("ground", Some("https://example.org/storey_class"))
        );
        assert_eq!(storey.functions().next().unwrap().value(), "living");
        assert!(storey.usages().next().is_none());
        assert!(storey.lod1_solid().is_none());
        assert!(storey.lod0_multi_surface().is_none());
        assert!(unit.class().is_none());
        assert_eq!(unit.usages().next().unwrap().value(), "residential");

        // The concrete types, from the features.
        let mut features = city_model.iter_features();
        let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
        let storeys: Vec<_> = features
            .iter()
            .filter_map(|f| Storey::try_from(f))
            .collect();
        assert_eq!(storeys.len(), 1);
        assert_eq!(storeys[0].feature_id().as_str(), "storey_ground");
        assert_eq!(storeys[0].functions().next().unwrap().value(), "living");
        let units: Vec<_> = features
            .iter()
            .filter_map(|f| BuildingUnit::try_from(f))
            .collect();
        assert_eq!(units[0].usages().next().unwrap().value(), "residential");

        let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
        let plain = read(path.as_bytes()).unwrap();
        assert!(
            first_building(&plain)
                .building_subdivisions()
                .next()
                .is_none()
        );
    }
}
