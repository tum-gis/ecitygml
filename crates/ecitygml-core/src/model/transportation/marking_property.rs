use crate::model::common::arena::ArenaProperty;
use crate::model::transportation::Marking;

/// A marking held inline or by `xlink:href`, corresponding to `tran:MarkingPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `transportation.xsd`).
pub type MarkingProperty = ArenaProperty<Marking>;
