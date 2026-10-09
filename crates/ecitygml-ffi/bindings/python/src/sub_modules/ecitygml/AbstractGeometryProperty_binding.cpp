#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryProperty.hpp"

namespace ecitygml {
void add_AbstractGeometryProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractGeometryProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractGeometryProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractGeometryProperty> opaque(mod, "AbstractGeometryProperty", nb::type_slots(ecitygml_AbstractGeometryProperty_slots), "A geometry property (inline geometry and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractGeometryProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractGeometryProperty::object, nb::rv_policy::reference_internal, "The inline geometry; none if the property only references one via `href`.");
}

} 