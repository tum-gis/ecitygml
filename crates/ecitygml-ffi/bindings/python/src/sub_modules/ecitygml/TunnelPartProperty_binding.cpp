#include "diplomat_nanobind_common.hpp"


#include "TunnelPartProperty.hpp"

namespace ecitygml {
void add_TunnelPartProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelPartProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelPartProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelPartProperty> opaque(mod, "TunnelPartProperty", nb::type_slots(ecitygml_TunnelPartProperty_slots), "A tunnel part property (inline tunnel part and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::TunnelPartProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::TunnelPartProperty::object, nb::rv_policy::reference_internal, "The inline tunnel part; none if the property only references one via `href`.");
}

} 