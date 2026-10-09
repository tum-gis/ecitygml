#include "diplomat_nanobind_common.hpp"


#include "AuxiliaryTrafficSpaceProperty.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficSpaceProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficSpaceProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficSpaceProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficSpaceProperty> opaque(mod, "AuxiliaryTrafficSpaceProperty", nb::type_slots(ecitygml_AuxiliaryTrafficSpaceProperty_slots), "A auxiliary traffic space property (inline auxiliary traffic space and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AuxiliaryTrafficSpaceProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AuxiliaryTrafficSpaceProperty::object, nb::rv_policy::reference_internal, "The inline auxiliary traffic space; none if the property only references one via `href`.");
}

} 