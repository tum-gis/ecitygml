#include "diplomat_nanobind_common.hpp"


#include "MarkingClassValue.hpp"

namespace ecitygml {
void add_MarkingClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MarkingClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::MarkingClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MarkingClassValue> opaque(mod, "MarkingClassValue", nb::type_slots(ecitygml_MarkingClassValue_slots), "The `class` property of a Marking.");
    opaque
        .def("code", &ecitygml::MarkingClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::MarkingClassValue::value);
}

} 