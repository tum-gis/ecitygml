#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficSpaceClassValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficSpaceClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficSpaceClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficSpaceClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficSpaceClassValue> opaque(mod, "AuxiliaryTrafficSpaceClassValue", nb::type_slots(ecitygml_AuxiliaryTrafficSpaceClassValue_slots), "The `class` property of an AuxiliaryTrafficSpace.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficSpaceClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficSpaceClassValue::value);
}

} 