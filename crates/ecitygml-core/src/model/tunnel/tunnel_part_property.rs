use crate::model::common::arena::ArenaProperty;
use crate::model::tunnel::TunnelPart;

/// A tunnel part held inline or by `xlink:href`, corresponding to `tun:TunnelPartPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `tunnel.xsd`).
pub type TunnelPartProperty = ArenaProperty<TunnelPart>;
