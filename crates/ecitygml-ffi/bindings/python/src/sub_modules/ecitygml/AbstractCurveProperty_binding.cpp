#include "diplomat_nanobind_common.hpp"


#include "AbstractCurveProperty.hpp"

namespace ecitygml {
void add_AbstractCurveProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCurveProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCurveProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCurveProperty> opaque(mod, "AbstractCurveProperty", nb::type_slots(ecitygml_AbstractCurveProperty_slots), "A curve property (inline curve and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::AbstractCurveProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::AbstractCurveProperty::object, nb::rv_policy::reference_internal, "The inline curve; none if the property only references one via `href`.");
}

} 