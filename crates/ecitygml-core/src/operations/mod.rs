mod geometry_collector;
mod traits;
mod visitor;

#[doc(inline)]
pub use visitor::Interpreter;

#[doc(inline)]
pub use visitor::CityObjectVisitor;

#[doc(inline)]
pub use visitor::Visitable;

#[doc(inline)]
pub use traits::FeatureWithGeometry;

#[doc(inline)]
pub use geometry_collector::GeometryCollector;

#[doc(inline)]
pub use geometry_collector::CityObjectGeometryCollection;

/*#[doc(inline)]
pub use traits::SpaceFeature;

#[doc(inline)]
pub use traits::GeometryId;

#[doc(inline)]
pub use traits::GeometryCollection;
*/
