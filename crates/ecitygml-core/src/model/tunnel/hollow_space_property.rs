use crate::model::common::arena::ArenaProperty;
use crate::model::tunnel::HollowSpace;

/// A hollow space held inline or by `xlink:href`, corresponding to `tun:HollowSpacePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `tunnel.xsd`).
pub type HollowSpaceProperty = ArenaProperty<HollowSpace>;
