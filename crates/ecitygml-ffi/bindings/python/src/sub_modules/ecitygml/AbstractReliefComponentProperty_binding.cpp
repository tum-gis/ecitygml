#include "diplomat_nanobind_common.hpp"


#include "AbstractReliefComponentProperty.hpp"

namespace ecitygml {
void add_AbstractReliefComponentProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractReliefComponentProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractReliefComponentProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractReliefComponentProperty> opaque(mod, "AbstractReliefComponentProperty", nb::type_slots(ecitygml_AbstractReliefComponentProperty_slots), "A relief component property (inline relief component and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractReliefComponentProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractReliefComponentProperty::object, nb::rv_policy::reference_internal, "The inline relief component; none if the property only references one via `href`.");
}

} 