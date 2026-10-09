use crate::model::common::arena::ArenaProperty;
use crate::model::core::AbstractPointCloudKind;

/// A point cloud held inline or by `xlink:href`, corresponding to `core:AbstractPointCloudPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type AbstractPointCloudProperty = ArenaProperty<AbstractPointCloudKind>;
