#include "diplomat_nanobind_common.hpp"


#include "BridgeFunctionValue.hpp"

namespace ecitygml {
void add_BridgeFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BridgeFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BridgeFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BridgeFunctionValue> opaque(mod, "BridgeFunctionValue", nb::type_slots(ecitygml_BridgeFunctionValue_slots), "The `function` property of a Bridge or BridgePart.");
    opaque
        .def("code", &ecitygml::BridgeFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BridgeFunctionValue::value);
}

} 