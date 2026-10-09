#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficAreaFunctionValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficAreaFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficAreaFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficAreaFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficAreaFunctionValue> opaque(mod, "AuxiliaryTrafficAreaFunctionValue", nb::type_slots(ecitygml_AuxiliaryTrafficAreaFunctionValue_slots), "The `function` property of an AuxiliaryTrafficArea.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficAreaFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficAreaFunctionValue::value);
}

} 