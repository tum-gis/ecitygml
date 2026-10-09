//! `ReliefFeature` and `TinRelief` (AbstractReliefComponent, a space boundary).

use crate::*;

use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::common::level_of_detail::LevelOfDetail;
use ecitygml_ffi::citygml::core::model::relief::relief_feature::ReliefFeature;
use ecitygml_ffi::citygml::core::model::relief::tin_relief::TinRelief;

// No fixture contains a relief: the FZK LoD2 header is reused with a single member.
const MEMBER: &str = r#"<cityObjectMember>
    <dem:ReliefFeature gml:id="relief_1">
      <dem:lod>2</dem:lod>
      <dem:reliefComponent>
        <dem:TINRelief gml:id="tin_1">
          <dem:lod>1</dem:lod>
          <dem:tin>
            <gml:TriangulatedSurface>
              <gml:patches>
                <gml:Triangle>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 0 1 0 0 0 1 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Triangle>
              </gml:patches>
            </gml:TriangulatedSurface>
          </dem:tin>
        </dem:TINRelief>
      </dem:reliefComponent>
    </dem:ReliefFeature>
  </cityObjectMember>
</CityModel>
"#;

#[test]
fn relief_feature_and_tin_relief() {
    let city_model = read_member(MEMBER);
    let relief = first(&city_model, ReliefFeature::try_from);
    assert_eq!(relief.feature_id().as_str(), "relief_1");
    assert_eq!(relief.lod(), LevelOfDetail::Two);

    // AbstractReliefComponentKind: feature type and the getters of every ancestor.
    let mut components = relief.relief_components();
    let component = components.next().unwrap();
    assert!(components.next().is_none());
    assert!(component.href().is_none());
    let component = component.object().unwrap();
    assert_eq!(component.feature_type(), FeatureType::TinRelief);
    assert_eq!(component.feature_id().as_str(), "tin_1");
    assert_eq!(component.lod(), LevelOfDetail::One);

    let tin = first(&city_model, TinRelief::try_from);
    assert_eq!(tin.lod(), LevelOfDetail::One);
    let surface = tin.tin().unwrap().object().unwrap();
    let mut triangles = surface.triangles();
    assert_eq!(std::iter::from_fn(|| triangles.next()).count(), 1);
    assert!((surface.area_3d().unwrap() - 0.5).abs() < 1e-9);
}
