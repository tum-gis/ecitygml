//! `DateTime` (`xs:dateTime`), mirroring `egml::model::xs::DateTime`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::Error;
    use diplomat_runtime::DiplomatWrite;
    use std::fmt::Write;

    /// A date and time of day with a timezone, created or borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct DateTime(pub(crate) egml::model::xs::DateTime);

    impl DateTime {
        /// Creates a date-time from its local fields and the offset east of UTC in seconds; fails with
        /// `InvalidArgument` for invalid fields or offsets.
        #[diplomat::attr(auto, named_constructor = "from_parts")]
        #[allow(clippy::too_many_arguments)] // mirrors egml's `DateTime::from_parts`
        pub fn from_parts(
            year: i32,
            month: u32,
            day: u32,
            hour: u32,
            minute: u32,
            second: u32,
            nanosecond: u32,
            offset_seconds: i32,
        ) -> Result<Box<DateTime>, Box<Error>> {
            Ok(Box::new(DateTime(egml::model::xs::DateTime::from_parts(
                year,
                month,
                day,
                hour,
                minute,
                second,
                nanosecond,
                offset_seconds,
            )?)))
        }

        pub fn year(&self) -> i32 {
            self.0.year()
        }

        /// 1 to 12.
        pub fn month(&self) -> u32 {
            self.0.month()
        }

        /// 1 to 31.
        pub fn day(&self) -> u32 {
            self.0.day()
        }

        pub fn hour(&self) -> u32 {
            self.0.hour()
        }

        pub fn minute(&self) -> u32 {
            self.0.minute()
        }

        pub fn second(&self) -> u32 {
            self.0.second()
        }

        pub fn nanosecond(&self) -> u32 {
            self.0.nanosecond()
        }

        /// The UTC offset in seconds (local time minus UTC), e.g. 3600 for `+01:00`.
        pub fn offset_seconds(&self) -> i32 {
            self.0.offset_seconds()
        }

        /// RFC 3339 / ISO 8601 representation, e.g. `2017-01-23T00:00:00+01:00` (via `as_chrono()`;
        /// egml has no lexical form yet).
        pub fn to_rfc3339(&self, write: &mut DiplomatWrite) {
            let _ = write.write_str(&self.0.as_chrono().to_rfc3339());
        }

        /// Seconds since the Unix epoch (1970-01-01T00:00:00Z) (via `as_chrono()`).
        pub fn timestamp(&self) -> i64 {
            self.0.as_chrono().timestamp()
        }

        /// Nanoseconds beyond the full seconds of `timestamp` (via `as_chrono()`).
        pub fn timestamp_subsec_nanos(&self) -> u32 {
            self.0.as_chrono().timestamp_subsec_nanos()
        }
    }
}

pub use ffi::DateTime;
