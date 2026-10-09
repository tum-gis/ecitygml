#include "diplomat_nanobind_common.hpp"


#include "BuildingSubdivisionClassValue.hpp"

namespace ecitygml {
void add_BuildingSubdivisionClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingSubdivisionClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingSubdivisionClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingSubdivisionClassValue> opaque(mod, "BuildingSubdivisionClassValue", nb::type_slots(ecitygml_BuildingSubdivisionClassValue_slots), "The `class` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).");
    opaque
        .def("code", &ecitygml::BuildingSubdivisionClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingSubdivisionClassValue::value);
}

} 