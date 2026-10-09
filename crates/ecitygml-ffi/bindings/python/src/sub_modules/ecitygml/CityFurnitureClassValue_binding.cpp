#include "diplomat_nanobind_common.hpp"


#include "CityFurnitureClassValue.hpp"

namespace ecitygml {
void add_CityFurnitureClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityFurnitureClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityFurnitureClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityFurnitureClassValue> opaque(mod, "CityFurnitureClassValue", nb::type_slots(ecitygml_CityFurnitureClassValue_slots), "The `class` property of a CityFurniture.");
    opaque
        .def("code", &ecitygml::CityFurnitureClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::CityFurnitureClassValue::value);
}

} 