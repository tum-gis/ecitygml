use crate::model::common::arena::ArenaProperty;
use crate::model::transportation::Hole;

/// A hole held inline or by `xlink:href`, corresponding to `tran:HolePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `transportation.xsd`).
pub type HoleProperty = ArenaProperty<Hole>;
