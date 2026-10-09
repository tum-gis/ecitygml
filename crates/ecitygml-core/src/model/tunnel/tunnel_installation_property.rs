use crate::model::common::arena::ArenaProperty;
use crate::model::tunnel::TunnelInstallation;

/// A tunnel installation held inline or by `xlink:href`, corresponding to `tun:TunnelInstallationPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `tunnel.xsd`).
pub type TunnelInstallationProperty = ArenaProperty<TunnelInstallation>;
