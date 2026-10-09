#include "diplomat_nanobind_common.hpp"


#include "SolitaryVegetationObjectFunctionValue.hpp"

namespace ecitygml {
void add_SolitaryVegetationObjectFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SolitaryVegetationObjectFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SolitaryVegetationObjectFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SolitaryVegetationObjectFunctionValue> opaque(mod, "SolitaryVegetationObjectFunctionValue", nb::type_slots(ecitygml_SolitaryVegetationObjectFunctionValue_slots), "The `function` property of a SolitaryVegetationObject.");
    opaque
        .def("code", &ecitygml::SolitaryVegetationObjectFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SolitaryVegetationObjectFunctionValue::value);
}

} 