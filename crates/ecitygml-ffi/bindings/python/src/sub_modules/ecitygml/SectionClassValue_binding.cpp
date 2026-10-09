#include "diplomat_nanobind_common.hpp"


#include "SectionClassValue.hpp"

namespace ecitygml {
void add_SectionClassValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SectionClassValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SectionClassValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SectionClassValue> opaque(mod, "SectionClassValue", nb::type_slots(ecitygml_SectionClassValue_slots), "The `class` property of a Section.");
    opaque
        .def("code", &ecitygml::SectionClassValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SectionClassValue::value);
}

} 