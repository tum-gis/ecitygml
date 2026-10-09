//! `Date` and `DateTime`.

use crate::*;

#[test]
fn xs_date_and_date_time() {
    use ecitygml_ffi::gml::core::model::xs::date::Date;
    use ecitygml_ffi::gml::core::model::xs::date_time::DateTime;

    let date = Date::from_parts(2020, 1, 2, 3600).unwrap();
    assert_eq!((date.year(), date.month(), date.day()), (2020, 1, 2));
    assert_eq!(date.offset_seconds(), 3600);
    let start = date.start_of_day();
    assert_eq!(
        written(|w| start.to_rfc3339(w)),
        "2020-01-02T00:00:00+01:00"
    );
    assert_eq!((start.hour(), start.minute(), start.second()), (0, 0, 0));

    let date_time = DateTime::from_parts(2017, 1, 23, 13, 14, 15, 500_000_000, -7200).unwrap();
    assert_eq!(
        (date_time.year(), date_time.month(), date_time.day()),
        (2017, 1, 23)
    );
    assert_eq!(
        (date_time.hour(), date_time.minute(), date_time.second()),
        (13, 14, 15)
    );
    assert_eq!(date_time.nanosecond(), 500_000_000);
    assert_eq!(date_time.offset_seconds(), -7200);
    assert_eq!(date_time.timestamp_subsec_nanos(), 500_000_000);

    let invalid = Date::from_parts(2021, 2, 30, 0).err().unwrap();
    assert_eq!(invalid.kind(), ErrorKind::InvalidArgument);
    let bad_offset = DateTime::from_parts(2020, 1, 1, 0, 0, 0, 0, 30)
        .err()
        .unwrap();
    assert_eq!(bad_offset.kind(), ErrorKind::InvalidArgument);
}
