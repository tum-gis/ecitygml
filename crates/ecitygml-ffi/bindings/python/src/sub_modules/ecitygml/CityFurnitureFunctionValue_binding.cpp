#include "diplomat_nanobind_common.hpp"


#include "CityFurnitureFunctionValue.hpp"

namespace ecitygml {
void add_CityFurnitureFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityFurnitureFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityFurnitureFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityFurnitureFunctionValue> opaque(mod, "CityFurnitureFunctionValue", nb::type_slots(ecitygml_CityFurnitureFunctionValue_slots), "The `function` property of a CityFurniture.");
    opaque
        .def("code", &ecitygml::CityFurnitureFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::CityFurnitureFunctionValue::value);
}

} 