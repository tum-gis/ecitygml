#include "diplomat_nanobind_common.hpp"


#include "PlantCoverUsageValue.hpp"

namespace ecitygml {
void add_PlantCoverUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PlantCoverUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::PlantCoverUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PlantCoverUsageValue> opaque(mod, "PlantCoverUsageValue", nb::type_slots(ecitygml_PlantCoverUsageValue_slots), "The `usage` property of a PlantCover.");
    opaque
        .def("code", &ecitygml::PlantCoverUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::PlantCoverUsageValue::value);
}

} 