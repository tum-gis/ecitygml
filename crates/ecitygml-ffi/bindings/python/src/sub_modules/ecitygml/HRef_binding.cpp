#include "diplomat_nanobind_common.hpp"


#include "HRef.hpp"

namespace ecitygml {
void add_HRef_binding(nb::module_ mod) {
    PyType_Slot ecitygml_HRef_slots[] = {
        {Py_tp_free, (void *)ecitygml::HRef::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::HRef> opaque(mod, "HRef", nb::type_slots(ecitygml_HRef_slots), "An `xlink:href` reference (local `#id` or remote URI), borrowed from a city model.");
    opaque
        .def("is_local", &ecitygml::HRef::is_local)
        .def("local_id", &ecitygml::HRef::local_id, "The referenced `gml:id` of a local reference (`#id`), or none for a remote one.")
        .def("to_string", &ecitygml::HRef::to_string, "The reference as written in GML (Rust: `Display`).");
}

} 