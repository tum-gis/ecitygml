#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficSpaceFunctionValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficSpaceFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficSpaceFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficSpaceFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficSpaceFunctionValue> opaque(mod, "AuxiliaryTrafficSpaceFunctionValue", nb::type_slots(ecitygml_AuxiliaryTrafficSpaceFunctionValue_slots), "The `function` property of an AuxiliaryTrafficSpace.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficSpaceFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficSpaceFunctionValue::value);
}

} 