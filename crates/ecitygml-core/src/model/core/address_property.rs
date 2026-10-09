use crate::model::core::Address;
use egml::model::base::Property;

/// An address held inline or by `xlink:href`, corresponding to `core:AddressPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type AddressProperty = Property<Address>;
