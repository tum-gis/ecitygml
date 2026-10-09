#include "diplomat_nanobind_common.hpp"


#include "IntersectionClassValue.hpp"

namespace ecitygml {
void add_IntersectionClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_IntersectionClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::IntersectionClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::IntersectionClassValue> opaque(mod, "IntersectionClassValue", nb::type_slots(ecitygml_IntersectionClassValue_slots), "The `class` property of an Intersection.");
    opaque
        .def("code", &ecitygml::IntersectionClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::IntersectionClassValue::value);
}

} 