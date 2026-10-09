//! `CityFurniture` (an occupied space).

use crate::*;

use ecitygml_ffi::citygml::core::model::city_furniture::city_furniture::CityFurniture;

// No fixture contains city furniture: the FZK LoD2 header is reused with a single member.
const MEMBER: &str = r#"<cityObjectMember>
    <frn:CityFurniture gml:id="sign_1">
      <gml:name>Vorschriftzeichen</gml:name>
      <lod2MultiSurface>
        <gml:MultiSurface>
          <gml:surfaceMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:surfaceMember>
        </gml:MultiSurface>
      </lod2MultiSurface>
      <frn:class codeSpace="https://example.org/furniture_class">1000</frn:class>
      <frn:function>1080</frn:function>
      <frn:usage>1090</frn:usage>
    </frn:CityFurniture>
  </cityObjectMember>
</CityModel>
"#;

#[test]
fn city_furniture() {
    let city_model = read_member(MEMBER);
    let furniture = first(&city_model, CityFurniture::try_from);
    assert_eq!(furniture.feature_id().as_str(), "sign_1");
    let class = furniture.class().unwrap();
    assert_eq!(
        (class.value(), class.code().code_space()),
        ("1000", Some("https://example.org/furniture_class"))
    );
    assert_eq!(furniture.functions().next().unwrap().value(), "1080");
    assert_eq!(furniture.usages().next().unwrap().value(), "1090");
    assert!(furniture.lod2_multi_surface().unwrap().object().is_some());
    assert!(furniture.lod1_implicit_representation().is_none());
    assert!(furniture.lod2_terrain_intersection_curve().is_none());
}
