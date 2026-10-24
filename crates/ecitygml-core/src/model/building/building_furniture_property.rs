use crate::model::building::BuildingFurniture;
use crate::model::common::arena::ArenaProperty;

/// A building furniture held inline or by `xlink:href`, corresponding to `bldg:BuildingFurniturePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type BuildingFurnitureProperty = ArenaProperty<BuildingFurniture>;
