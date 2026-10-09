#include "diplomat_nanobind_common.hpp"


#include "BuildingPartProperty.hpp"

namespace ecitygml {
void add_BuildingPartProperty_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingPartProperty_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingPartProperty::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingPartProperty> opaque(mod, "BuildingPartProperty", nb::type_slots(ecitygml_BuildingPartProperty_slots), "A building part property (inline building part and/or `xlink:href`), borrowed from a city model.");
    opaque
        .def("href", &ecitygml::BuildingPartProperty::href, nb::rv_policy::reference_internal)
        .def("object", &ecitygml::BuildingPartProperty::object, nb::rv_policy::reference_internal, "The inline building part; none if the property only references one via `href`.");
}

} 