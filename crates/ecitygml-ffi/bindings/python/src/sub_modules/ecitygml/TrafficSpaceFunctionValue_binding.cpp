#include "diplomat_nanobind_common.hpp"


#include "TrafficSpaceFunctionValue.hpp"

namespace ecitygml {
void add_TrafficSpaceFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpaceFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpaceFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpaceFunctionValue> opaque(mod, "TrafficSpaceFunctionValue", nb::type_slots(ecitygml_TrafficSpaceFunctionValue_slots), "The `function` property of a TrafficSpace.");
    opaque
        .def("code", &ecitygml::TrafficSpaceFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficSpaceFunctionValue::value);
}

} 