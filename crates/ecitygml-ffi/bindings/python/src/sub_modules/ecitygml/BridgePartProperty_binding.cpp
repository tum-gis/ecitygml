#include "diplomat_nanobind_common.hpp"


#include "BridgePartProperty.hpp"

namespace ecitygml {
void add_BridgePartProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BridgePartProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::BridgePartProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BridgePartProperty> opaque(mod, "BridgePartProperty", nb::type_slots(ecitygml_BridgePartProperty_slots), "A bridge part property (inline bridge part and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::BridgePartProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::BridgePartProperty::object, nb::rv_policy::reference_internal, "The inline bridge part; none if the property only references one via `href`.");
}

} 