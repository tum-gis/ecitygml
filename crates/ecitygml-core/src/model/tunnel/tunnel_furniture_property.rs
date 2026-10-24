use crate::model::common::arena::ArenaProperty;
use crate::model::tunnel::TunnelFurniture;

/// A tunnel furniture held inline or by `xlink:href`, corresponding to `tun:TunnelFurniturePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `tunnel.xsd`).
pub type TunnelFurnitureProperty = ArenaProperty<TunnelFurniture>;
