#include "diplomat_nanobind_common.hpp"


#include "RoadUsageValue.hpp"

namespace ecitygml {
void add_RoadUsageValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RoadUsageValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::RoadUsageValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RoadUsageValue> opaque(mod, "RoadUsageValue", nb::type_slots(ecitygml_RoadUsageValue_slots), "The `usage` property of a Road.");
    opaque
        .def("code", &ecitygml::RoadUsageValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::RoadUsageValue::value);
}

} 