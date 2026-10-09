#include "diplomat_nanobind_common.hpp"


#include "TrafficSpaceUsageValue.hpp"

namespace ecitygml {
void add_TrafficSpaceUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpaceUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpaceUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpaceUsageValue> opaque(mod, "TrafficSpaceUsageValue", nb::type_slots(ecitygml_TrafficSpaceUsageValue_slots), "The `usage` property of a TrafficSpace.");
    opaque
        .def("code", &ecitygml::TrafficSpaceUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficSpaceUsageValue::value);
}

} 