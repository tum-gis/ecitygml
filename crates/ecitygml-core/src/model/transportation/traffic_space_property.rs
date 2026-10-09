use crate::model::common::arena::ArenaProperty;
use crate::model::transportation::TrafficSpace;

/// A traffic space held inline or by `xlink:href`, corresponding to `tran:TrafficSpacePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `transportation.xsd`).
pub type TrafficSpaceProperty = ArenaProperty<TrafficSpace>;
