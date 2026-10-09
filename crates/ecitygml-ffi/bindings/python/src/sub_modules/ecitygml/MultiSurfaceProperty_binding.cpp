#include "diplomat_nanobind_common.hpp"


#include "MultiSurfaceProperty.hpp"

namespace ecitygml {
void add_MultiSurfaceProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MultiSurfaceProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::MultiSurfaceProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MultiSurfaceProperty> opaque(mod, "MultiSurfaceProperty", nb::type_slots(ecitygml_MultiSurfaceProperty_slots), "A multi-surface property (inline multi surface and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::MultiSurfaceProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::MultiSurfaceProperty::object, nb::rv_policy::reference_internal, "The inline multi surface; none if the property only references one via `href`.");
}

} 