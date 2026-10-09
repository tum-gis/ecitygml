#include "diplomat_nanobind_common.hpp"


#include "MarkingProperty.hpp"

namespace ecitygml {
void add_MarkingProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MarkingProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::MarkingProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MarkingProperty> opaque(mod, "MarkingProperty", nb::type_slots(ecitygml_MarkingProperty_slots), "A marking property (inline marking and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::MarkingProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::MarkingProperty::object, nb::rv_policy::reference_internal, "The inline marking; none if the property only references one via `href`.");
}

} 