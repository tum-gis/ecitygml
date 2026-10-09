#include "diplomat_nanobind_common.hpp"


#include "BridgeUsageValue.hpp"

namespace ecitygml {
void add_BridgeUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BridgeUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BridgeUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BridgeUsageValue> opaque(mod, "BridgeUsageValue", nb::type_slots(ecitygml_BridgeUsageValue_slots), "The `usage` property of a Bridge or BridgePart.");
    opaque
        .def("code", &ecitygml::BridgeUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BridgeUsageValue::value);
}

} 