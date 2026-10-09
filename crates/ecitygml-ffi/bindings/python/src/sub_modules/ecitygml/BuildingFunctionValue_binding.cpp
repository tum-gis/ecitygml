#include "diplomat_nanobind_common.hpp"


#include "BuildingFunctionValue.hpp"

namespace ecitygml {
void add_BuildingFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingFunctionValue> opaque(mod, "BuildingFunctionValue", nb::type_slots(ecitygml_BuildingFunctionValue_slots), "The `function` property of a Building or BuildingPart.");
    opaque
        .def("code", &ecitygml::BuildingFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingFunctionValue::value);
}

} 