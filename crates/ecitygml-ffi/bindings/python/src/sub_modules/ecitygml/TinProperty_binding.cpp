#include "diplomat_nanobind_common.hpp"


#include "TinProperty.hpp"

namespace ecitygml {
void add_TinProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TinProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::TinProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TinProperty> opaque(mod, "TinProperty", nb::type_slots(ecitygml_TinProperty_slots), "A TIN property (inline triangulated surface and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::TinProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::TinProperty::object, nb::rv_policy::reference_internal, "The inline triangulated surface; none if the property only references one via `href`.");
}

} 