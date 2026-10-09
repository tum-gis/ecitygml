#include "diplomat_nanobind_common.hpp"


#include "Formatting.hpp"

namespace ecitygml {
void add_Formatting_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Formatting_slots[] = {
        {Py_tp_free, (void *)ecitygml::Formatting::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Formatting> opaque(mod, "Formatting", nb::type_slots(ecitygml_Formatting_slots), "How written GML is laid out. Rust's enum variant `Indent` carries data, which Diplomat enums\ncan't, so each variant is a named constructor.");
    opaque
        .def_static("compact", std::move(maybe_op_unwrap(&ecitygml::Formatting::compact)), "All elements on a single line, without whitespace between them.")
        .def_static("indent", std::move(maybe_op_unwrap(&ecitygml::Formatting::indent)), "char"_a, "size"_a, "Each element on its own line, indented by `size` repetitions of the byte `char`, e.g.\n`b' '` and 2.")
        .def_static("new_line", std::move(maybe_op_unwrap(&ecitygml::Formatting::new_line)), "Each element on its own line, without indentation (the default).");
}

} 