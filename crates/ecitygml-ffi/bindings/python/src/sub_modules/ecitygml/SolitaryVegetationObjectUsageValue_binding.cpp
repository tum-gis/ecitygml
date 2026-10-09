#include "diplomat_nanobind_common.hpp"


#include "SolitaryVegetationObjectUsageValue.hpp"

namespace ecitygml {
void add_SolitaryVegetationObjectUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SolitaryVegetationObjectUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SolitaryVegetationObjectUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SolitaryVegetationObjectUsageValue> opaque(mod, "SolitaryVegetationObjectUsageValue", nb::type_slots(ecitygml_SolitaryVegetationObjectUsageValue_slots), "The `usage` property of a SolitaryVegetationObject.");
    opaque
        .def("code", &ecitygml::SolitaryVegetationObjectUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SolitaryVegetationObjectUsageValue::value);
}

} 