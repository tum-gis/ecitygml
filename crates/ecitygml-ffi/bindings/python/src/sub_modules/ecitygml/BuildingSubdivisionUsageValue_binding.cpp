#include "diplomat_nanobind_common.hpp"


#include "BuildingSubdivisionUsageValue.hpp"

namespace ecitygml {
void add_BuildingSubdivisionUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingSubdivisionUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingSubdivisionUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingSubdivisionUsageValue> opaque(mod, "BuildingSubdivisionUsageValue", nb::type_slots(ecitygml_BuildingSubdivisionUsageValue_slots), "The `usage` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).");
    opaque
        .def("code", &ecitygml::BuildingSubdivisionUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::BuildingSubdivisionUsageValue::value);
}

} 