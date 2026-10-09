#include "diplomat_nanobind_common.hpp"


#include "DateTime.hpp"

namespace ecitygml {
void add_DateTime_binding(nb::module_ mod) {
    PyType_Slot ecitygml_DateTime_slots[] = {
        {Py_tp_free, (void *)ecitygml::DateTime::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::DateTime> opaque(mod, "DateTime", nb::type_slots(ecitygml_DateTime_slots), "A date and time of day with a timezone, created or borrowed from a city model.");
    opaque
        .def("day", &ecitygml::DateTime::day, "1 to 31.")
        .def_static("from_parts", std::move(maybe_op_unwrap(&ecitygml::DateTime::from_parts)), "year"_a, "month"_a, "day"_a, "hour"_a, "minute"_a, "second"_a, "nanosecond"_a, "offset_seconds"_a, "Creates a date-time from its local fields and the offset east of UTC in seconds; fails with\n`InvalidArgument` for invalid fields or offsets.")
        .def("hour", &ecitygml::DateTime::hour)
        .def("minute", &ecitygml::DateTime::minute)
        .def("month", &ecitygml::DateTime::month, "1 to 12.")
        .def("nanosecond", &ecitygml::DateTime::nanosecond)
        .def("offset_seconds", &ecitygml::DateTime::offset_seconds, "The UTC offset in seconds (local time minus UTC), e.g. 3600 for `+01:00`.")
        .def("second", &ecitygml::DateTime::second)
        .def("timestamp", &ecitygml::DateTime::timestamp, "Seconds since the Unix epoch (1970-01-01T00:00:00Z) (via `as_chrono()`).")
        .def("timestamp_subsec_nanos", &ecitygml::DateTime::timestamp_subsec_nanos, "Nanoseconds beyond the full seconds of `timestamp` (via `as_chrono()`).")
        .def("to_rfc3339", &ecitygml::DateTime::to_rfc3339, "RFC 3339 / ISO 8601 representation, e.g. `2017-01-23T00:00:00+01:00` (via `as_chrono()`;\negml has no lexical form yet).")
        .def("year", &ecitygml::DateTime::year);
}

} 