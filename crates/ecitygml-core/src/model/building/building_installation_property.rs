use crate::model::building::BuildingInstallation;
use crate::model::common::arena::ArenaProperty;

/// A building installation held inline or by `xlink:href`, corresponding to `bldg:BuildingInstallationPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type BuildingInstallationProperty = ArenaProperty<BuildingInstallation>;
