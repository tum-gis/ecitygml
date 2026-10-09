#include "diplomat_nanobind_common.hpp"


#include "CityFurnitureUsageValue.hpp"

namespace ecitygml {
void add_CityFurnitureUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityFurnitureUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityFurnitureUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityFurnitureUsageValue> opaque(mod, "CityFurnitureUsageValue", nb::type_slots(ecitygml_CityFurnitureUsageValue_slots), "The `usage` property of a CityFurniture.");
    opaque
        .def("code", &ecitygml::CityFurnitureUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::CityFurnitureUsageValue::value);
}

} 