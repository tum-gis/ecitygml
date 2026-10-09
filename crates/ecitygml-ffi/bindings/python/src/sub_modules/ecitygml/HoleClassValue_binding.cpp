#include "diplomat_nanobind_common.hpp"


#include "HoleClassValue.hpp"

namespace ecitygml {
void add_HoleClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_HoleClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::HoleClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::HoleClassValue> opaque(mod, "HoleClassValue", nb::type_slots(ecitygml_HoleClassValue_slots), "The `class` property of a Hole.");
    opaque
        .def("code", &ecitygml::HoleClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::HoleClassValue::value);
}

} 