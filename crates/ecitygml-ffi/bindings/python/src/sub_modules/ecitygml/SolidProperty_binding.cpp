#include "diplomat_nanobind_common.hpp"


#include "SolidProperty.hpp"

namespace ecitygml {
void add_SolidProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SolidProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::SolidProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SolidProperty> opaque(mod, "SolidProperty", nb::type_slots(ecitygml_SolidProperty_slots), "A solid property (inline solid and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::SolidProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::SolidProperty::object, nb::rv_policy::reference_internal, "The inline solid; none if the property only references one via `href`.");
}

} 