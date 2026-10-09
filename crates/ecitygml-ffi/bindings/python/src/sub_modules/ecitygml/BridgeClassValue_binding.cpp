#include "diplomat_nanobind_common.hpp"


#include "BridgeClassValue.hpp"

namespace ecitygml {
void add_BridgeClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BridgeClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BridgeClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BridgeClassValue> opaque(mod, "BridgeClassValue", nb::type_slots(ecitygml_BridgeClassValue_slots), "The `class` property of a Bridge or BridgePart.");
    opaque
        .def("code", &ecitygml::BridgeClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BridgeClassValue::value);
}

} 