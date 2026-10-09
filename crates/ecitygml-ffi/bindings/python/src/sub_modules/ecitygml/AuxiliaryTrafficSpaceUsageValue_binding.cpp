#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficSpaceUsageValue.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficSpaceUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficSpaceUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficSpaceUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficSpaceUsageValue> opaque(mod, "AuxiliaryTrafficSpaceUsageValue", nb::type_slots(ecitygml_AuxiliaryTrafficSpaceUsageValue_slots), "The `usage` property of an AuxiliaryTrafficSpace.");
    opaque
        .def("code", &ecitygml::AuxiliaryTrafficSpaceUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::AuxiliaryTrafficSpaceUsageValue::value);
}

} 