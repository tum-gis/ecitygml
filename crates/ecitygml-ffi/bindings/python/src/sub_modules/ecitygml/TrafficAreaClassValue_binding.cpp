#include "diplomat_nanobind_common.hpp"


#include "TrafficAreaClassValue.hpp"

namespace ecitygml {
void add_TrafficAreaClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficAreaClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficAreaClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficAreaClassValue> opaque(mod, "TrafficAreaClassValue", nb::type_slots(ecitygml_TrafficAreaClassValue_slots), "The `class` property of a TrafficArea.");
    opaque
        .def("code", &ecitygml::TrafficAreaClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficAreaClassValue::value);
}

} 