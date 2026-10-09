#include "diplomat_nanobind_common.hpp"


#include "TrafficAreaUsageValue.hpp"

namespace ecitygml {
void add_TrafficAreaUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficAreaUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficAreaUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficAreaUsageValue> opaque(mod, "TrafficAreaUsageValue", nb::type_slots(ecitygml_TrafficAreaUsageValue_slots), "The `usage` property of a TrafficArea.");
    opaque
        .def("code", &ecitygml::TrafficAreaUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficAreaUsageValue::value);
}

} 