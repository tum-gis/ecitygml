#include "diplomat_nanobind_common.hpp"


#include "Date.hpp"

namespace ecitygml {
void add_Date_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Date_slots[] = {
        {Py_tp_free, (void *)ecitygml::Date::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Date> opaque(mod, "Date", nb::type_slots(ecitygml_Date_slots), "A calendar date with a timezone, created or borrowed from a city model.");
    opaque
        .def("day", &ecitygml::Date::day, "1 to 31.")
        .def_static("from_parts", std::move(maybe_op_unwrap(&ecitygml::Date::from_parts)), "year"_a, "month"_a, "day"_a, "offset_seconds"_a, "Creates a date from its fields and the offset east of UTC in seconds; fails with\n`InvalidArgument` for invalid fields or offsets.")
        .def("month", &ecitygml::Date::month, "1 to 12.")
        .def("offset_seconds", &ecitygml::Date::offset_seconds, "The UTC offset in seconds (local time minus UTC).")
        .def("start_of_day", std::move(maybe_op_unwrap(&ecitygml::Date::start_of_day)), "Midnight at the start of the date, in the date's timezone.")
        .def("year", &ecitygml::Date::year);
}

} 