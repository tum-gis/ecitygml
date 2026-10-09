#include "diplomat_nanobind_common.hpp"


#include "PlantCoverFunctionValue.hpp"

namespace ecitygml {
void add_PlantCoverFunctionValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PlantCoverFunctionValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::PlantCoverFunctionValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PlantCoverFunctionValue> opaque(mod, "PlantCoverFunctionValue", nb::type_slots(ecitygml_PlantCoverFunctionValue_slots), "The `function` property of a PlantCover.");
    opaque
        .def("code", &ecitygml::PlantCoverFunctionValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::PlantCoverFunctionValue::value);
}

} 