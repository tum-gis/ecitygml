#include "diplomat_nanobind_common.hpp"


#include "SpeciesValue.hpp"

namespace ecitygml {
void add_SpeciesValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SpeciesValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SpeciesValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SpeciesValue> opaque(mod, "SpeciesValue", nb::type_slots(ecitygml_SpeciesValue_slots), "The `species` property of a SolitaryVegetationObject.");
    opaque
        .def("code", &ecitygml::SpeciesValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SpeciesValue::value);
}

} 