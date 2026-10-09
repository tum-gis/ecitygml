#include "diplomat_nanobind_common.hpp"


#include "TrafficSpaceProperty.hpp"

namespace ecitygml {
void add_TrafficSpaceProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpaceProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpaceProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpaceProperty> opaque(mod, "TrafficSpaceProperty", nb::type_slots(ecitygml_TrafficSpaceProperty_slots), "A traffic space property (inline traffic space and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::TrafficSpaceProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::TrafficSpaceProperty::object, nb::rv_policy::reference_internal, "The inline traffic space; none if the property only references one via `href`.");
}

} 