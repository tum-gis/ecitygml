#include "diplomat_nanobind_common.hpp"


#include "AbstractBuildingSubdivisionProperty.hpp"

namespace ecitygml {
void add_AbstractBuildingSubdivisionProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractBuildingSubdivisionProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractBuildingSubdivisionProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractBuildingSubdivisionProperty> opaque(mod, "AbstractBuildingSubdivisionProperty", nb::type_slots(ecitygml_AbstractBuildingSubdivisionProperty_slots), "A building subdivision property (inline building subdivision and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractBuildingSubdivisionProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractBuildingSubdivisionProperty::object, nb::rv_policy::reference_internal, "The inline building subdivision; none if the property only references one via `href`.");
}

} 