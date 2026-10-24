//! `TrafficSpaceReference`, mirroring `ecitygml::model::transportation::TrafficSpaceReference`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A reference to a traffic space by `xlink:href`, borrowed from a city model. Like in Rust, it
    /// has no accessors of its own: convert it with `Reference::from_traffic_space_reference`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TrafficSpaceReference(
        pub(crate) ecitygml::model::transportation::TrafficSpaceReference,
    );

    /// Iterates over a list of traffic space references, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct TrafficSpaceReferenceIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::transportation::TrafficSpaceReference>,
    );

    impl<'a> TrafficSpaceReferenceIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a TrafficSpaceReference> {
            self.0
                .next()
                .map(TrafficSpaceReference::transparent_convert)
        }
    }
}

pub use ffi::{TrafficSpaceReference, TrafficSpaceReferenceIterator};
