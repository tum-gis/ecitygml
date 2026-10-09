#include "diplomat_nanobind_common.hpp"


#include "TrafficAreaFunctionValue.hpp"

namespace ecitygml {
void add_TrafficAreaFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficAreaFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficAreaFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficAreaFunctionValue> opaque(mod, "TrafficAreaFunctionValue", nb::type_slots(ecitygml_TrafficAreaFunctionValue_slots), "The `function` property of a TrafficArea.");
    opaque
        .def("code", &ecitygml::TrafficAreaFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TrafficAreaFunctionValue::value);
}

} 