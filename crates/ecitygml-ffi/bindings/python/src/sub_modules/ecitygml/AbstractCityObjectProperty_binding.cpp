#include "diplomat_nanobind_common.hpp"


#include "AbstractCityObjectProperty.hpp"

namespace ecitygml {
void add_AbstractCityObjectProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCityObjectProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCityObjectProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCityObjectProperty> opaque(mod, "AbstractCityObjectProperty", nb::type_slots(ecitygml_AbstractCityObjectProperty_slots), "A city object property (inline city object and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractCityObjectProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractCityObjectProperty::object, nb::rv_policy::reference_internal, "The inline city object; none if the property only references one via `href`.");
}

} 