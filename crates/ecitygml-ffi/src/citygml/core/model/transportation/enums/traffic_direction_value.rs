//! `TrafficDirectionValue`, mirroring `ecitygml::model::transportation::enums::TrafficDirectionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Allowed traffic direction of a traffic space.
    #[diplomat::enum_convert(ecitygml::model::transportation::enums::TrafficDirectionValue)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum TrafficDirectionValue {
        Forwards,
        Backwards,
        Both,
    }
}

pub use ffi::TrafficDirectionValue;
