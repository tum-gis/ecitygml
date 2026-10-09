//! `Date` (`xs:date`), mirroring `egml::model::xs::Date`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::xs::date_time::ffi::DateTime;

    /// A calendar date with a timezone, created or borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Date(egml::model::xs::Date);

    impl Date {
        /// Creates a date from its fields and the offset east of UTC in seconds; fails with
        /// `InvalidArgument` for invalid fields or offsets.
        #[diplomat::attr(auto, named_constructor = "from_parts")]
        pub fn from_parts(
            year: i32,
            month: u32,
            day: u32,
            offset_seconds: i32,
        ) -> Result<Box<Date>, Box<Error>> {
            Ok(Box::new(Date(egml::model::xs::Date::from_parts(
                year,
                month,
                day,
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

        /// The UTC offset in seconds (local time minus UTC).
        pub fn offset_seconds(&self) -> i32 {
            self.0.offset_seconds()
        }

        /// Midnight at the start of the date, in the date's timezone.
        pub fn start_of_day(&self) -> Box<DateTime> {
            Box::new(DateTime(self.0.start_of_day()))
        }
    }
}

pub use ffi::Date;
