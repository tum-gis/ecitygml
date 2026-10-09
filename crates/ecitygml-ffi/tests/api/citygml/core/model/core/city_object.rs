//! The AbstractCityObject getters `external_references`, `generic_attributes` and `related_to`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::generics::generic_attribute_kind::GenericAttributeKind;
use ecitygml_ffi::citygml::core::model::generics::generic_attribute_set::GenericAttributeSet;
use ecitygml_ffi::citygml::core::model::generics::measure_attribute::MeasureAttribute;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

// Properties absent from the fixtures, injected into a copy of the FZK LoD2 building.
const EXTRA_PROPERTIES: &str = r##"<relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>
      <relatedTo>
        <CityObjectRelation>
          <relationType>shared</relationType>
          <relatedTo xlink:href="#UUID_other"/>
          <genericAttribute>
            <gen:IntAttribute><gen:name>weight</gen:name><gen:value>3</gen:value></gen:IntAttribute>
          </genericAttribute>
        </CityObjectRelation>
      </relatedTo>
      <genericAttribute>
        <gen:GenericAttributeSet>
          <gen:name>energy</gen:name>
          <gen:genericAttribute>
            <gen:DoubleAttribute><gen:name>demand</gen:name><gen:value>12.5</gen:value></gen:DoubleAttribute>
          </gen:genericAttribute>
          <gen:genericAttribute>
            <gen:StringAttribute><gen:name>label</gen:name><gen:value>A+</gen:value></gen:StringAttribute>
          </gen:genericAttribute>
        </gen:GenericAttributeSet>
      </genericAttribute>"##;

fn first<'a, T: 'a>(
    city_model: &'a CityModel,
    try_from: impl Fn(&ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef<'a>) -> Option<&'a T>,
) -> &'a T {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|f| try_from(&f))
        .unwrap()
}

fn kinds<'a>(
    iterator: &mut ecitygml_ffi::citygml::core::model::generics::generic_attribute_kind::GenericAttributeKindIterator<'a>,
) -> Vec<&'a GenericAttributeKind> {
    std::iter::from_fn(|| iterator.next()).collect()
}

#[test]
fn external_references() {
    let city_model = read(format!("{FIXTURES}TUM-Main-Entrance.gml").as_bytes()).unwrap();
    let building = first(&city_model, |f| Building::try_from(f));
    let mut references = building.external_references();
    let reference = references.next().unwrap();
    assert!(references.next().is_none());
    assert_eq!(reference.target_resource(), "DEBYvAAAAABTMIyA");
    assert_eq!(
        reference.information_system(),
        Some("http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100")
    );
    assert!(reference.relation_type().is_none());

    let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    assert!(
        first(&city_model, |f| Building::try_from(f))
            .external_references()
            .next()
            .is_none()
    );
}

#[test]
fn generic_attribute_kinds_and_values() {
    let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let building = first(&city_model, |f| Building::try_from(f));
    let attributes = kinds(&mut building.generic_attributes());
    let names: Vec<_> = attributes.iter().map(|a| a.name()).collect();
    assert_eq!(
        names,
        ["GrossPlannedArea", "ConstructionMethod", "IsLandmarked"]
    );

    let measure = MeasureAttribute::try_from(attributes[0]).unwrap();
    assert!(attributes[0].as_string().is_none());
    assert_eq!(measure.name(), "GrossPlannedArea");
    assert_eq!(
        (measure.value().value(), measure.value().uom()),
        (120.0, "m2")
    );
    let method = attributes[1].as_string().unwrap();
    assert_eq!(
        (method.name(), method.value()),
        ("ConstructionMethod", "New Building")
    );
    assert!(MeasureAttribute::try_from(attributes[1]).is_none());

    // Thematic surfaces have the getters too.
    let wall = first(&city_model, |f| WallSurface::try_from(f));
    assert!(wall.generic_attributes().next().is_none());
}

#[test]
fn int_and_double_attributes() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let space = first(&city_model, |f| TrafficSpace::try_from(f));
    let attributes = kinds(&mut space.generic_attributes());
    let lane_id = attributes
        .iter()
        .find(|a| a.name() == "identifier_laneId")
        .unwrap();
    assert_eq!(lane_id.as_int().unwrap().value(), 1);
    assert!(lane_id.as_double().is_none());
    let length = attributes
        .iter()
        .find(|a| a.name() == "opendrive_road_length")
        .unwrap();
    assert_eq!(length.as_double().unwrap().value(), 40.0);
    assert_eq!(length.as_double().unwrap().name(), "opendrive_road_length");
}

#[test]
fn attribute_set_and_relation() {
    let city_model = read_fixture_modified(
        "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
        "<relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>",
        EXTRA_PROPERTIES,
    );
    let building = first(&city_model, |f| Building::try_from(f));
    let attributes = kinds(&mut building.generic_attributes());
    let set = GenericAttributeSet::try_from(attributes[0]).unwrap();
    assert_eq!(set.name(), "energy");
    let nested = kinds(&mut set.generic_attributes());
    assert_eq!(nested[0].as_double().unwrap().value(), 12.5);
    assert_eq!(nested[0].name(), "demand");
    assert_eq!(nested[1].as_string().unwrap().value(), "A+");

    let mut relations = building.related_to();
    let property = relations.next().unwrap();
    assert!(relations.next().is_none());
    assert!(property.href().is_none());
    let relation = property.object().unwrap();
    assert_eq!(relation.relation_type().value(), "shared");
    assert!(relation.relation_type().code().code_space().is_none());
    assert_eq!(
        relation.relation_to().href().unwrap().local_id(),
        Some("UUID_other")
    );
    let relation_attributes = kinds(&mut relation.generic_attributes());
    let weight = relation_attributes[0].as_int().unwrap();
    assert_eq!((weight.name(), weight.value()), ("weight", 3));

    let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
    let plain = read(path.as_bytes()).unwrap();
    assert!(
        first(&plain, |f| Building::try_from(f))
            .related_to()
            .next()
            .is_none()
    );
}
