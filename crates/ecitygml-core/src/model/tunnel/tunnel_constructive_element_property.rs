use crate::model::common::arena::ArenaProperty;
use crate::model::tunnel::TunnelConstructiveElement;

/// A tunnel constructive element held inline or by `xlink:href`, corresponding to `tun:TunnelConstructiveElementPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `tunnel.xsd`).
pub type TunnelConstructiveElementProperty = ArenaProperty<TunnelConstructiveElement>;
