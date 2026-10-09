#include "diplomat_nanobind_common.hpp"


#include "Code.hpp"

namespace ecitygml {
void add_Code_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Code_slots[] = {
        {Py_tp_free, (void *)ecitygml::Code::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Code> opaque(mod, "Code", nb::type_slots(ecitygml_Code_slots), "A code-list value with an optional code space, borrowed from a city model.");
    opaque
        .def("code_space", &ecitygml::Code::code_space)
        .def("value", &ecitygml::Code::value);
}

} 