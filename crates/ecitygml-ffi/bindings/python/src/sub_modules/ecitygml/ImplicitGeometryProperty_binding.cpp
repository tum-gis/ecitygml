#include "diplomat_nanobind_common.hpp"


#include "ImplicitGeometryProperty.hpp"

namespace ecitygml {
void add_ImplicitGeometryProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ImplicitGeometryProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::ImplicitGeometryProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ImplicitGeometryProperty> opaque(mod, "ImplicitGeometryProperty", nb::type_slots(ecitygml_ImplicitGeometryProperty_slots), "An implicit geometry property (inline implicit geometry and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::ImplicitGeometryProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::ImplicitGeometryProperty::object, nb::rv_policy::reference_internal, "The inline implicit geometry; none if the property only references one via `href`.");
}

} 