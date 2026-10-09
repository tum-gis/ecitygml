#include "diplomat_nanobind_common.hpp"


#include "HoleProperty.hpp"

namespace ecitygml {
void add_HoleProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_HoleProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::HoleProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::HoleProperty> opaque(mod, "HoleProperty", nb::type_slots(ecitygml_HoleProperty_slots), "A hole property (inline hole and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::HoleProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::HoleProperty::object, nb::rv_policy::reference_internal, "The inline hole; none if the property only references one via `href`.");
}

} 