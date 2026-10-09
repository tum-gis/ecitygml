#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfaceProperty.hpp"

namespace ecitygml {
void add_AbstractSurfaceProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSurfaceProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSurfaceProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSurfaceProperty> opaque(mod, "AbstractSurfaceProperty", nb::type_slots(ecitygml_AbstractSurfaceProperty_slots), "A surface property (inline surface and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractSurfaceProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractSurfaceProperty::object, nb::rv_policy::reference_internal, "The inline surface; none if the property only references one via `href`.");
}

} 