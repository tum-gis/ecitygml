#include "diplomat_nanobind_common.hpp"


#include "TunnelClassValue.hpp"

namespace ecitygml {
void add_TunnelClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelClassValue> opaque(mod, "TunnelClassValue", nb::type_slots(ecitygml_TunnelClassValue_slots), "The `class` property of a Tunnel or TunnelPart.");
    opaque
        .def("code", &ecitygml::TunnelClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::TunnelClassValue::value);
}

} 