#include "diplomat_nanobind_common.hpp"


#include "BuildingClassValue.hpp"

namespace ecitygml {
void add_BuildingClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingClassValue> opaque(mod, "BuildingClassValue", nb::type_slots(ecitygml_BuildingClassValue_slots), "The `class` property of a Building or BuildingPart.");
    opaque
        .def("code", &ecitygml::BuildingClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingClassValue::value);
}

} 