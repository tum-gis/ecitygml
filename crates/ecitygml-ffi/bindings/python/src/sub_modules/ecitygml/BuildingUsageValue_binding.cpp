#include "diplomat_nanobind_common.hpp"


#include "BuildingUsageValue.hpp"

namespace ecitygml {
void add_BuildingUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingUsageValue> opaque(mod, "BuildingUsageValue", nb::type_slots(ecitygml_BuildingUsageValue_slots), "The `usage` property of a Building or BuildingPart.");
    opaque
        .def("code", &ecitygml::BuildingUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingUsageValue::value);
}

} 