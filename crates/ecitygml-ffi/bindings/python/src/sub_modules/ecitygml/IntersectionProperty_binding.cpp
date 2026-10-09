#include "diplomat_nanobind_common.hpp"


#include "IntersectionProperty.hpp"

namespace ecitygml {
void add_IntersectionProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_IntersectionProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::IntersectionProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::IntersectionProperty> opaque(mod, "IntersectionProperty", nb::type_slots(ecitygml_IntersectionProperty_slots), "A intersection property (inline intersection and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::IntersectionProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::IntersectionProperty::object, nb::rv_policy::reference_internal, "The inline intersection; none if the property only references one via `href`.");
}

} 