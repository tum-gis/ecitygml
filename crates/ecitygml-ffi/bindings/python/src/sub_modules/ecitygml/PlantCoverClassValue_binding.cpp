#include "diplomat_nanobind_common.hpp"


#include "PlantCoverClassValue.hpp"

namespace ecitygml {
void add_PlantCoverClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PlantCoverClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::PlantCoverClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PlantCoverClassValue> opaque(mod, "PlantCoverClassValue", nb::type_slots(ecitygml_PlantCoverClassValue_slots), "The `class` property of a PlantCover.");
    opaque
        .def("code", &ecitygml::PlantCoverClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::PlantCoverClassValue::value);
}

} 