#include "diplomat_nanobind_common.hpp"


#include "TunnelUsageValue.hpp"

namespace ecitygml {
void add_TunnelUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelUsageValue> opaque(mod, "TunnelUsageValue", nb::type_slots(ecitygml_TunnelUsageValue_slots), "The `usage` property of a Tunnel or TunnelPart.");
    opaque
        .def("code", &ecitygml::TunnelUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TunnelUsageValue::value);
}

} 