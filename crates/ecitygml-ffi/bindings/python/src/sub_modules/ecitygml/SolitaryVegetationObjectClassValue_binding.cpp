#include "diplomat_nanobind_common.hpp"


#include "SolitaryVegetationObjectClassValue.hpp"

namespace ecitygml {
void add_SolitaryVegetationObjectClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SolitaryVegetationObjectClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SolitaryVegetationObjectClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SolitaryVegetationObjectClassValue> opaque(mod, "SolitaryVegetationObjectClassValue", nb::type_slots(ecitygml_SolitaryVegetationObjectClassValue_slots), "The `class` property of a SolitaryVegetationObject.");
    opaque
        .def("code", &ecitygml::SolitaryVegetationObjectClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SolitaryVegetationObjectClassValue::value);
}

} 