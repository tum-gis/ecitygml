#include "diplomat_nanobind_common.hpp"


#include "TunnelFunctionValue.hpp"

namespace ecitygml {
void add_TunnelFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelFunctionValue> opaque(mod, "TunnelFunctionValue", nb::type_slots(ecitygml_TunnelFunctionValue_slots), "The `function` property of a Tunnel or TunnelPart.");
    opaque
        .def("code", &ecitygml::TunnelFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TunnelFunctionValue::value);
}

} 