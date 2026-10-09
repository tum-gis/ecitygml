#include "diplomat_nanobind_common.hpp"


#include "CityObjectRelationProperty.hpp"

namespace ecitygml {
void add_CityObjectRelationProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityObjectRelationProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityObjectRelationProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityObjectRelationProperty> opaque(mod, "CityObjectRelationProperty", nb::type_slots(ecitygml_CityObjectRelationProperty_slots), "A city object relation property (inline relation and/or `xlink:href`), borrowed from a\ncity model.");
    opaque
        .def("href", &ecitygml::CityObjectRelationProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::CityObjectRelationProperty::object, nb::rv_policy::reference_internal, "The inline relation; none if the property only references one via `href`.");
}

} 