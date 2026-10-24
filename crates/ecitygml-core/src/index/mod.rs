//! Spatial indexing of city objects.
//!
//! [`BvhIndex`] is a bounding volume hierarchy over the axis-aligned bounding boxes of all city
//! objects of a model. It is a fast coarse filter at object level: queries return every object
//! whose box intersects the query box, and callers run exact geometric checks on the few results.
//!
//! # Example
//!
//! ```
//! use ecitygml_core::index::BvhIndex;
//! use ecitygml_core::model::core::{AbstractCityObjectProperty, AsAbstractSpaceMut, CityModel};
//! use ecitygml_core::model::transportation::Road;
//! use egml::model::base::Id;
//! use egml::model::geometry::aggregates::{MultiCurve, MultiCurveProperty};
//! use egml::model::geometry::primitives::{AbstractCurveProperty, LineString};
//! use egml::model::geometry::{DirectPosition, Envelope};
//!
//! # fn main() -> Result<(), Box<dyn std::error::Error>> {
//! // A road whose lod0 centre line runs from (0, 0, 0) to (100, 0, 0).
//! let centre_line = LineString::new([
//!     DirectPosition::new(0.0, 0.0, 0.0)?,
//!     DirectPosition::new(100.0, 0.0, 0.0)?,
//! ])?;
//! let mut road = Road::new(Id::try_from("road")?);
//! road.set_lod0_multi_curve(Some(MultiCurveProperty::from_object(MultiCurve::new([
//!     AbstractCurveProperty::from_object(centre_line.into()),
//! ])?)));
//! let mut city_model = CityModel::new(Id::try_from("city_model")?);
//! city_model.push_city_object_member(AbstractCityObjectProperty::from_object(road.into()));
//!
//! let index = BvhIndex::from_city_model(city_model)?;
//!
//! // An area five metres north of the road: missed by a plain query, found with a tolerance.
//! let area = Envelope::new(
//!     DirectPosition::new(40.0, 5.0, 0.0)?,
//!     DirectPosition::new(60.0, 10.0, 0.0)?,
//! )?;
//! assert_eq!(index.query_envelope(&area).count(), 0);
//! assert_eq!(index.query_envelope(&area.enlarge(5.0)?).count(), 1);
//! # Ok(())
//! # }
//! ```

mod bvh;
mod spatial_entry;

pub use bvh::BvhIndex;
