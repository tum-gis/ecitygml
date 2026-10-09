#include "diplomat_nanobind_common.hpp"


#include "PointProperty.hpp"

namespace ecitygml {
void add_PointProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PointProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::PointProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PointProperty> opaque(mod, "PointProperty", nb::type_slots(ecitygml_PointProperty_slots), "A point property (inline point and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::PointProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::PointProperty::object, nb::rv_policy::reference_internal, "The inline point; none if the property only references one via `href`.");
}

} 