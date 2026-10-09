#include "diplomat_nanobind_common.hpp"


#include "SectionProperty.hpp"

namespace ecitygml {
void add_SectionProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SectionProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::SectionProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SectionProperty> opaque(mod, "SectionProperty", nb::type_slots(ecitygml_SectionProperty_slots), "A section property (inline section and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::SectionProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::SectionProperty::object, nb::rv_policy::reference_internal, "The inline section; none if the property only references one via `href`.");
}

} 