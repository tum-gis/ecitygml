#include "diplomat_nanobind_common.hpp"


#include "MultiCurveProperty.hpp"

namespace ecitygml {
void add_MultiCurveProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MultiCurveProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::MultiCurveProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MultiCurveProperty> opaque(mod, "MultiCurveProperty", nb::type_slots(ecitygml_MultiCurveProperty_slots), "A multi-curve property (inline multi curve and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::MultiCurveProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::MultiCurveProperty::object, nb::rv_policy::reference_internal, "The inline multi curve; none if the property only references one via `href`.");
}

} 