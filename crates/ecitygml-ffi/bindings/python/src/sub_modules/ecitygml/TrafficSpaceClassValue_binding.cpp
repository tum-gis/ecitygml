#include "diplomat_nanobind_common.hpp"


#include "TrafficSpaceClassValue.hpp"

namespace ecitygml {
void add_TrafficSpaceClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpaceClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpaceClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpaceClassValue> opaque(mod, "TrafficSpaceClassValue", nb::type_slots(ecitygml_TrafficSpaceClassValue_slots), "The `class` property of a TrafficSpace.");
    opaque
        .def("code", &ecitygml::TrafficSpaceClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficSpaceClassValue::value);
}

} 