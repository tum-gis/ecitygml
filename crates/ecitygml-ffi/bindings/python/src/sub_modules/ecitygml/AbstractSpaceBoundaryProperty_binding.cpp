#include "diplomat_nanobind_common.hpp"


#include "AbstractSpaceBoundaryProperty.hpp"

namespace ecitygml {
void add_AbstractSpaceBoundaryProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSpaceBoundaryProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSpaceBoundaryProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSpaceBoundaryProperty> opaque(mod, "AbstractSpaceBoundaryProperty", nb::type_slots(ecitygml_AbstractSpaceBoundaryProperty_slots), "A space boundary property (inline space boundary and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractSpaceBoundaryProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractSpaceBoundaryProperty::object, nb::rv_policy::reference_internal, "The inline space boundary; none if the property only references one via `href`.");
}

} 