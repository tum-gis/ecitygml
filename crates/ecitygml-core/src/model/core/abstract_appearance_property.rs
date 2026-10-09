use crate::model::common::arena::ArenaProperty;
use crate::model::core::AbstractAppearanceKind;

/// An appearance held inline or by `xlink:href`, corresponding to `core:AbstractAppearancePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type AbstractAppearanceProperty = ArenaProperty<AbstractAppearanceKind>;
