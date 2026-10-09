#include "diplomat_nanobind_common.hpp"


#include "RoadFunctionValue.hpp"

namespace ecitygml {
void add_RoadFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RoadFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::RoadFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RoadFunctionValue> opaque(mod, "RoadFunctionValue", nb::type_slots(ecitygml_RoadFunctionValue_slots), "The `function` property of a Road.");
    opaque
        .def("code", &ecitygml::RoadFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::RoadFunctionValue::value);
}

} 