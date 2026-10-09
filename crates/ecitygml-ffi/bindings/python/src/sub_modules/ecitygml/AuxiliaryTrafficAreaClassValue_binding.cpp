#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficAreaClassValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficAreaClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficAreaClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficAreaClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficAreaClassValue> opaque(mod, "AuxiliaryTrafficAreaClassValue", nb::type_slots(ecitygml_AuxiliaryTrafficAreaClassValue_slots), "The `class` property of an AuxiliaryTrafficArea.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficAreaClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficAreaClassValue::value);
}

} 