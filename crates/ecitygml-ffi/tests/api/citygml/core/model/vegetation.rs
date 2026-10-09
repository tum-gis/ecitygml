//! `SolitaryVegetationObject` and `PlantCover` (AbstractVegetationObject, an occupied space).

use crate::*;

use ecitygml_ffi::citygml::core::model::vegetation::plant_cover::PlantCover;
use ecitygml_ffi::citygml::core::model::vegetation::solitary_vegetation_object::SolitaryVegetationObject;

// No fixture contains vegetation: the FZK LoD2 header is reused with a single member.
const TREE: &str = r#"<cityObjectMember>
    <veg:SolitaryVegetationObject gml:id="tree_1">
      <lod1ImplicitRepresentation>
        <ImplicitGeometry gml:id="tree_prototype">
          <transformationMatrix>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</transformationMatrix>
          <referencePoint><gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point></referencePoint>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>
      <veg:class codeSpace="https://example.org/tree_class">1000</veg:class>
      <veg:function>1010</veg:function>
      <veg:usage>1020</veg:usage>
      <veg:species>Quercus robur</veg:species>
      <veg:height uom="m">12.5</veg:height>
      <veg:trunkDiameter uom="m">0.4</veg:trunkDiameter>
      <veg:crownDiameter uom="m">5.5</veg:crownDiameter>
      <veg:rootBallDiameter uom="m">1.2</veg:rootBallDiameter>
      <veg:maxRootBallDepth uom="m">0.8</veg:maxRootBallDepth>
    </veg:SolitaryVegetationObject>
  </cityObjectMember>
</CityModel>
"#;

const PLANT_COVER: &str = r#"<cityObjectMember>
    <veg:PlantCover gml:id="cover_1">
      <veg:class>2000</veg:class>
      <veg:averageHeight uom="m">2.5</veg:averageHeight>
      <veg:minHeight uom="m">1</veg:minHeight>
      <veg:maxHeight uom="m">4</veg:maxHeight>
    </veg:PlantCover>
  </cityObjectMember>
</CityModel>
"#;

#[test]
fn solitary_vegetation_object() {
    let city_model = read_member(TREE);
    let tree = first(&city_model, SolitaryVegetationObject::try_from);
    assert_eq!(tree.feature_id().as_str(), "tree_1");
    let class = tree.class().unwrap();
    assert_eq!(
        (class.value(), class.code().code_space()),
        ("1000", Some("https://example.org/tree_class"))
    );
    assert_eq!(tree.functions().next().unwrap().value(), "1010");
    assert_eq!(tree.usages().next().unwrap().value(), "1020");
    assert_eq!(tree.species().unwrap().value(), "Quercus robur");
    let height = tree.height().unwrap();
    assert_eq!((height.value(), height.uom()), (12.5, "m"));
    assert_eq!(tree.trunk_diameter().unwrap().value(), 0.4);
    assert_eq!(tree.crown_diameter().unwrap().value(), 5.5);
    assert_eq!(tree.root_ball_diameter().unwrap().value(), 1.2);
    assert_eq!(tree.max_root_ball_depth().unwrap().value(), 0.8);

    // AbstractOccupiedSpace, AbstractPhysicalSpace and AbstractSpace getters.
    let implicit = tree
        .lod1_implicit_representation()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(implicit.object_id().as_str(), "tree_prototype");
    assert!(tree.lod1_terrain_intersection_curve().is_none());
    assert!(tree.lod1_solid().is_none());
}

#[test]
fn plant_cover() {
    let city_model = read_member(PLANT_COVER);
    let cover = first(&city_model, PlantCover::try_from);
    assert_eq!(cover.feature_id().as_str(), "cover_1");
    assert_eq!(cover.class().unwrap().value(), "2000");
    assert!(cover.functions().next().is_none());
    assert!(cover.usages().next().is_none());
    assert_eq!(cover.average_height().unwrap().value(), 2.5);
    assert_eq!(cover.min_height().unwrap().value(), 1.0);
    assert_eq!(cover.max_height().unwrap().value(), 4.0);
    assert!(cover.lod1_implicit_representation().is_none());
    assert!(
        SolitaryVegetationObject::try_from(&city_model.iter_features().next().unwrap()).is_none()
    );
}
