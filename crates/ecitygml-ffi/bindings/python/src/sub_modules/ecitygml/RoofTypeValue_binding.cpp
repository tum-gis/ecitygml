#include "diplomat_nanobind_common.hpp"


#include "RoofTypeValue.hpp"

namespace ecitygml {
void add_RoofTypeValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RoofTypeValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::RoofTypeValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RoofTypeValue> opaque(mod, "RoofTypeValue", nb::type_slots(ecitygml_RoofTypeValue_slots), "The `roofType` property of a Building or BuildingPart.");
    opaque
        .def("code", &ecitygml::RoofTypeValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::RoofTypeValue::value);
}

} 