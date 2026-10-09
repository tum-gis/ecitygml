#include "diplomat_nanobind_common.hpp"


#include "AbstractFillingSurfaceProperty.hpp"

namespace ecitygml {
void add_AbstractFillingSurfaceProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractFillingSurfaceProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractFillingSurfaceProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractFillingSurfaceProperty> opaque(mod, "AbstractFillingSurfaceProperty", nb::type_slots(ecitygml_AbstractFillingSurfaceProperty_slots), "A filling surface property (inline filling surface and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractFillingSurfaceProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractFillingSurfaceProperty::object, nb::rv_policy::reference_internal, "The inline filling surface; none if the property only references one via `href`.");
}

} 