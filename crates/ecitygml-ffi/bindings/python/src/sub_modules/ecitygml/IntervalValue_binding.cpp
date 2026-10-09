#include "diplomat_nanobind_common.hpp"


#include "IntervalValue.hpp"

namespace ecitygml {
void add_IntervalValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_IntervalValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::IntervalValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::IntervalValue> opaque(mod, "IntervalValue", nb::type_slots(ecitygml_IntervalValue_slots), "The `interval` property of an Occupancy.");
    opaque
        .def("code", &ecitygml::IntervalValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::IntervalValue::value);
}

} 