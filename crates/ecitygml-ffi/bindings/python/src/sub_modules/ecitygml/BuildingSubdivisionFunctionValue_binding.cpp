#include "diplomat_nanobind_common.hpp"


#include "BuildingSubdivisionFunctionValue.hpp"

namespace ecitygml {
void add_BuildingSubdivisionFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingSubdivisionFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingSubdivisionFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingSubdivisionFunctionValue> opaque(mod, "BuildingSubdivisionFunctionValue", nb::type_slots(ecitygml_BuildingSubdivisionFunctionValue_slots), "The `function` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).");
    opaque
        .def("code", &ecitygml::BuildingSubdivisionFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingSubdivisionFunctionValue::value);
}

} 