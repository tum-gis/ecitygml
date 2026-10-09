#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficAreaUsageValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficAreaUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficAreaUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficAreaUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficAreaUsageValue> opaque(mod, "AuxiliaryTrafficAreaUsageValue", nb::type_slots(ecitygml_AuxiliaryTrafficAreaUsageValue_slots), "The `usage` property of an AuxiliaryTrafficArea.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficAreaUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficAreaUsageValue::value);
}

} 