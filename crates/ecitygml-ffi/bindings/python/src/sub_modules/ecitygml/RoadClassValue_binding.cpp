#include "diplomat_nanobind_common.hpp"


#include "RoadClassValue.hpp"

namespace ecitygml {
void add_RoadClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RoadClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::RoadClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RoadClassValue> opaque(mod, "RoadClassValue", nb::type_slots(ecitygml_RoadClassValue_slots), "The `class` property of a Road.");
    opaque
        .def("code", &ecitygml::RoadClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::RoadClassValue::value);
}

} 