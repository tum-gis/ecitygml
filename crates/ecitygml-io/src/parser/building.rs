use crate::Error;
use ecitygml_core::model::building::Building;
use ecitygml_core::model::construction::{
    DoorSurface, GroundSurface, RoofSurface, WallSurface, WindowSurface,
};
use ecitygml_core::model::core::{CityObject, OccupiedSpace, Space, ThematicSurface};
use egml::io::GmlMultiSurfaceProperty;
use egml::model::base::{Gml, Id};
use quick_xml::de;
use serde::{Deserialize, Serialize};
use std::hash::{DefaultHasher, Hash, Hasher};
use tracing::warn;

pub fn parse_building(id: &Id, xml_document: &String) -> Result<Building, Error> {
    let mut building = Building::new(id.clone());
    // todo: building.occupied_space = parse_occupied_space(&xml_document)?;

    // TODO: remove extended snippet
    let mut parent_xml_snippet: String = xml_document.trim().to_string();
    parent_xml_snippet.insert_str(0, "<bldg:Building>");
    parent_xml_snippet.push_str("</bldg:Building>");
    let gml_building: GmlBuilding = de::from_str(&parent_xml_snippet).expect("");

    building.roof_surface = gml_building
        .boundary
        .iter()
        .flat_map(|x| &x.roof_surface)
        .map(|x| x.clone().try_into())
        .collect::<Result<Vec<_>, Error>>()?;
    building.wall_surface = gml_building
        .boundary
        .iter()
        .flat_map(|x| &x.wall_surface)
        .map(|x| x.clone().try_into())
        .collect::<Result<Vec<_>, Error>>()?;
    building.ground_surface = gml_building
        .boundary
        .iter()
        .flat_map(|x| &x.ground_surface)
        .map(|x| x.clone().try_into())
        .collect::<Result<Vec<_>, Error>>()?;

    Ok(building)
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "bldg:Building")]
struct GmlBuilding {
    #[serde(rename = "boundary")]
    pub boundary: Vec<GmlBoundary>,
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "boundary")]
struct GmlBoundary {
    #[serde(rename = "GroundSurface")]
    pub ground_surface: Option<GmlGroundSurface>,
    #[serde(rename = "RoofSurface")]
    pub roof_surface: Option<GmlRoofSurface>,
    #[serde(rename = "WallSurface")]
    pub wall_surface: Option<GmlWallSurface>,
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:RoofSurface")]
struct GmlRoofSurface {
    #[serde(rename = "@id", default)]
    id: String,

    #[serde(rename = "lod2MultiSurface")]
    pub lod2_multi_surface: Option<GmlMultiSurfaceProperty>,
    #[serde(rename = "lod3MultiSurface")]
    pub lod3_multi_surface: Option<GmlMultiSurfaceProperty>,
}

impl TryFrom<GmlRoofSurface> for RoofSurface {
    type Error = Error;

    fn try_from(value: GmlRoofSurface) -> Result<Self, Self::Error> {
        let id: Id = value.id.clone().try_into().ok().unwrap_or_else(|| {
            let mut hasher = DefaultHasher::new();
            value.hash(&mut hasher);
            Id::from_hashed_u64(hasher.finish())
        });
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);
        let thematic_surface = ThematicSurface::new(city_object);
        let mut roof_surface = RoofSurface::new(thematic_surface);

        if let Some(g) = value.lod2_multi_surface.and_then(|x| x.multi_surface) {
            roof_surface.thematic_surface.lod2_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod2_multi_surface of RoofSurface with id {}: {}",
                        &roof_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }
        if let Some(g) = value.lod3_multi_surface.and_then(|x| x.multi_surface) {
            roof_surface.thematic_surface.lod3_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod3_multi_surface of RoofSurface with id {}: {}",
                        &roof_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }

        Ok(roof_surface)
    }
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:GroundSurface")]
struct GmlGroundSurface {
    #[serde(rename = "@id", default)]
    id: String,

    #[serde(rename = "lod2MultiSurface")]
    pub lod2_multi_surface: Option<GmlMultiSurfaceProperty>,
    #[serde(rename = "lod3MultiSurface")]
    pub lod3_multi_surface: Option<GmlMultiSurfaceProperty>,
}

impl TryFrom<GmlGroundSurface> for GroundSurface {
    type Error = Error;

    fn try_from(value: GmlGroundSurface) -> Result<Self, Self::Error> {
        let id: Id = value.id.clone().try_into().ok().unwrap_or_else(|| {
            let mut hasher = DefaultHasher::new();
            value.hash(&mut hasher);
            Id::from_hashed_u64(hasher.finish())
        });
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);
        let thematic_surface = ThematicSurface::new(city_object);
        let mut ground_surface = GroundSurface::new(thematic_surface);

        if let Some(g) = value.lod2_multi_surface.and_then(|x| x.multi_surface) {
            ground_surface.thematic_surface.lod2_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod2_multi_surface of GroundSurface with id {}: {}",
                        &ground_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }
        if let Some(g) = value.lod3_multi_surface.and_then(|x| x.multi_surface) {
            ground_surface.thematic_surface.lod3_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod3_multi_surface of GroundSurface with id {}: {}",
                        &ground_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }

        Ok(ground_surface)
    }
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:WallSurface")]
struct GmlWallSurface {
    #[serde(rename = "@id", default)]
    id: String,

    #[serde(rename = "lod2MultiSurface")]
    pub lod2_multi_surface: Option<GmlMultiSurfaceProperty>,
    #[serde(rename = "lod3MultiSurface")]
    pub lod3_multi_surface: Option<GmlMultiSurfaceProperty>,

    #[serde(rename = "fillingSurface", default)]
    pub filling_surface: Vec<GmlFillingSurface>,
}

impl TryFrom<GmlWallSurface> for WallSurface {
    type Error = Error;

    fn try_from(value: GmlWallSurface) -> Result<Self, Self::Error> {
        let id: Id = value.id.clone().try_into().ok().unwrap_or_else(|| {
            let mut hasher = DefaultHasher::new();
            value.hash(&mut hasher);
            Id::from_hashed_u64(hasher.finish())
        });
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);
        let thematic_surface = ThematicSurface::new(city_object);
        let mut wall_surface = WallSurface::new(thematic_surface);

        if let Some(g) = value.lod2_multi_surface.and_then(|x| x.multi_surface) {
            wall_surface.thematic_surface.lod2_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod2_multi_surface of WallSurface with id {}: {}",
                        &wall_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }
        if let Some(g) = value.lod3_multi_surface.and_then(|x| x.multi_surface) {
            wall_surface.thematic_surface.lod3_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod3_multi_surface of WallSurface with id {}: {}",
                        &wall_surface.thematic_surface.city_object.gml.id, x
                    )
                })
                .ok();
        }

        wall_surface.door_surface = value
            .filling_surface
            .iter()
            .flat_map(|x| &x.door_surface)
            .flat_map(|x| {
                x.clone()
                    .try_into()
                    .map_err(|e| {
                        warn!(
                            "Error parsing lod2_multi_surface of WallSurface with id {}: {}",
                            &wall_surface.thematic_surface.city_object.gml.id, e
                        )
                    })
                    .ok()
            })
            .collect();

        wall_surface.window_surface = value
            .filling_surface
            .iter()
            .flat_map(|x| &x.window_surface)
            .flat_map(|x| {
                x.clone()
                    .try_into()
                    .map_err(|e| {
                        warn!(
                            "Error parsing lod2_multi_surface of WallSurface with id {}: {}",
                            &wall_surface.thematic_surface.city_object.gml.id, e
                        )
                    })
                    .ok()
            })
            .collect();

        Ok(wall_surface)
    }
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:fillingSurface")]
struct GmlFillingSurface {
    #[serde(rename = "WindowSurface")]
    pub window_surface: Option<GmlWindowSurface>,
    #[serde(rename = "DoorSurface")]
    pub door_surface: Option<GmlDoorSurface>,
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:WindowSurface")]
struct GmlWindowSurface {
    #[serde(rename = "@id")]
    id: String,

    #[serde(rename = "lod3MultiSurface")]
    pub lod3_multi_surface: Option<GmlMultiSurfaceProperty>,
}

impl TryFrom<GmlWindowSurface> for WindowSurface {
    type Error = Error;

    fn try_from(value: GmlWindowSurface) -> Result<Self, Self::Error> {
        let id: Id = value.id.clone().try_into().ok().unwrap_or_else(|| {
            let mut hasher = DefaultHasher::new();
            value.hash(&mut hasher);
            Id::from_hashed_u64(hasher.finish())
        });
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);
        let space = Space::new(city_object);
        let occupied_space = OccupiedSpace::new(space);
        let mut window_surface = WindowSurface::new(occupied_space);

        if let Some(g) = value.lod3_multi_surface.unwrap().multi_surface {
            window_surface.occupied_space.space.lod3_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod3_multi_surface of WallSurface with id {}: {}",
                        &window_surface.occupied_space.space.city_object.gml.id, x
                    )
                })
                .ok();
        }

        Ok(window_surface)
    }
}

#[derive(Debug, Serialize, Deserialize, PartialEq, Hash, Clone)]
#[serde(rename = "con:DoorSurface")]
struct GmlDoorSurface {
    #[serde(rename = "@id")]
    id: String,

    #[serde(rename = "lod3MultiSurface")]
    pub lod3_multi_surface: Option<GmlMultiSurfaceProperty>,
}

impl TryFrom<GmlDoorSurface> for DoorSurface {
    type Error = Error;

    fn try_from(value: GmlDoorSurface) -> Result<Self, Self::Error> {
        let id: Id = value.id.clone().try_into().ok().unwrap_or_else(|| {
            let mut hasher = DefaultHasher::new();
            value.hash(&mut hasher);
            Id::from_hashed_u64(hasher.finish())
        });
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);
        let space = Space::new(city_object);
        let occupied_space = OccupiedSpace::new(space);
        let mut door_surface = DoorSurface::new(occupied_space);

        if let Some(g) = value.lod3_multi_surface.unwrap().multi_surface {
            door_surface.occupied_space.space.lod3_multi_surface = g
                .try_into()
                .map_err(|x| {
                    warn!(
                        "Error parsing lod3_multi_surface of WallSurface with id {}: {}",
                        &door_surface.occupied_space.space.city_object.gml.id, x
                    )
                })
                .ok();
        }

        Ok(door_surface)
    }
}

#[cfg(test)]
mod tests_serde {
    use crate::parser::building::{GmlWallSurface, GmlWindowSurface};
    use ecitygml_core::model::construction::{WallSurface, WindowSurface};
    use quick_xml::de;

    #[test]
    fn parsing_basic_wall_surface() {
        let source_text = "<con:WallSurface gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7\">
        <lod3MultiSurface>
            <gml:MultiSurface srsName=\"EPSG:25832\" srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly\">
                  <gml:exterior>
                    <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly_0_\">
                      <gml:posList>691013.788 5336016.141 527.279 691032.4 5336008.882 527.279 691039.961 5336028.267 527.279 691024.783 5336034.186 527.279 691021.426 5336035.513 527.279 691013.788 5336016.141 527.279</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                  <gml:interior>
                    <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly_0_.8u9i9Ny3nmKEiTNUHM4H\">
                      <gml:posList>691023.387 5336030.606 527.279 691034.471 5336026.213 527.279 691030.099 5336015.127 527.279 691019.004 5336019.491 527.279 691023.387 5336030.606 527.279</gml:posList>
                    </gml:LinearRing>
                  </gml:interior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod3MultiSurface>
          <con:fillingSurface>
            <con:WindowSurface gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm\">
              <lod3MultiSurface>
                <gml:MultiSurface srsName=\"EPSG:25832\" srsDimension=\"3\">
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.ykiWAbKjhs5FuBIUnynb\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xnqUQ3qMkvPzo9s5lR6C\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.747 5336007.243 527.991 691042.746 5336007.243 527.991 691042.246 5336005.983 527.991 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.NbvSzQarqjFERBjHwvjJ\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xLeYfMNQEAXXs0SFqvXN\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.246 5336005.983 527.991 691042.246 5336005.983 529.829 691042.247 5336005.983 529.829 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>
          </con:fillingSurface>
       </con:WallSurface>";

        let gml_wall_surface: GmlWallSurface = de::from_str(source_text).expect("");
        assert_eq!(
            &gml_wall_surface.id,
            "DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7"
        );
        assert_eq!(
            gml_wall_surface
                .filling_surface
                .first()
                .expect("must be there")
                .window_surface
                .as_ref()
                .expect("must be there")
                .id,
            "DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm"
        );
        let wall_surface: WallSurface = gml_wall_surface.try_into().expect("");

        assert_eq!(
            wall_surface
                .thematic_surface
                .lod3_multi_surface
                .as_ref()
                .expect("must be there")
                .surface_member()
                .len(),
            1
        );
        assert_eq!(
            wall_surface
                .window_surface
                .first()
                .expect("must be there")
                .occupied_space
                .space
                .lod3_multi_surface
                .as_ref()
                .expect("must be there")
                .surface_member()
                .len(),
            2
        );
    }

    #[test]
    fn parsing_wall_surface() {
        let source_text = "<con:WallSurface gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7\">
        <lod3MultiSurface>
            <gml:MultiSurface srsName=\"EPSG:25832\" srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly\">
                  <gml:exterior>
                    <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly_0_\">
                      <gml:posList>691013.788 5336016.141 527.279 691032.4 5336008.882 527.279 691039.961 5336028.267 527.279 691024.783 5336034.186 527.279 691021.426 5336035.513 527.279 691013.788 5336016.141 527.279</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                  <gml:interior>
                    <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7_poly_0_.8u9i9Ny3nmKEiTNUHM4H\">
                      <gml:posList>691023.387 5336030.606 527.279 691034.471 5336026.213 527.279 691030.099 5336015.127 527.279 691019.004 5336019.491 527.279 691023.387 5336030.606 527.279</gml:posList>
                    </gml:LinearRing>
                  </gml:interior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod3MultiSurface>
          <con:fillingSurface>
            <con:WindowSurface gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm\">
              <lod3MultiSurface>
                <gml:MultiSurface srsName=\"EPSG:25832\" srsDimension=\"3\">
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.ykiWAbKjhs5FuBIUnynb\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xnqUQ3qMkvPzo9s5lR6C\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.747 5336007.243 527.991 691042.746 5336007.243 527.991 691042.246 5336005.983 527.991 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.NbvSzQarqjFERBjHwvjJ\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xLeYfMNQEAXXs0SFqvXN\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.246 5336005.983 527.991 691042.246 5336005.983 529.829 691042.247 5336005.983 529.829 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>
          </con:fillingSurface>
      </con:WallSurface>";

        let gml_wall_surface: GmlWallSurface = de::from_str(source_text).expect("");
        assert_eq!(
            &gml_wall_surface.id,
            "DEBY_LOD2_4959457_e030de07-0827-4f7b-9657-9070e768b8f7"
        );
        assert_eq!(
            gml_wall_surface
                .filling_surface
                .first()
                .expect("must be there")
                .window_surface
                .as_ref()
                .expect("must be there")
                .id,
            "DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm"
        );
        let wall_surface: WallSurface = gml_wall_surface.try_into().expect("");
    }

    #[test]
    fn parsing_window_surface() {
        let source_text = "<con:WindowSurface gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm\">
              <lod3MultiSurface>
                <gml:MultiSurface srsName=\"EPSG:25832\" srsDimension=\"3\">
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.ykiWAbKjhs5FuBIUnynb\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xnqUQ3qMkvPzo9s5lR6C\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.747 5336007.243 527.991 691042.746 5336007.243 527.991 691042.246 5336005.983 527.991 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_PG.NbvSzQarqjFERBjHwvjJ\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"DEBY_LOD2_4959457_BP.Omsr1bTUsLJnOfathXJm_LR.xLeYfMNQEAXXs0SFqvXN\">
                          <gml:posList>691042.247 5336005.983 527.991 691042.246 5336005.983 527.991 691042.246 5336005.983 529.829 691042.247 5336005.983 529.829 691042.247 5336005.983 527.991</gml:posList>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>";

        let gml_window_surface: GmlWindowSurface = de::from_str(source_text).expect("");
        let window_surface: WindowSurface = gml_window_surface.try_into().expect("");
    }
}
