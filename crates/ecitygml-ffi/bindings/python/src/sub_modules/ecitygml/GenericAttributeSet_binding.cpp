#include "diplomat_nanobind_common.hpp"


#include "GenericAttributeKind.hpp"
#include "GenericAttributeSet.hpp"

namespace ecitygml {
void add_GenericAttributeSet_binding(nb::module_ mod) {
    PyType_Slot ecitygml_GenericAttributeSet_slots[] = {
        {Py_tp_free, (void *)ecitygml::GenericAttributeSet::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::GenericAttributeSet> opaque(mod, "GenericAttributeSet", nb::type_slots(ecitygml_GenericAttributeSet_slots), "A named set of generic attributes, borrowed from a city model.");
    opaque
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::GenericAttributeSet::generic_attributes)), nb::keep_alive<0, 1>())
        .def("name", &ecitygml::GenericAttributeSet::name)
        .def_static("try_from", &ecitygml::GenericAttributeSet::try_from, "attribute"_a, nb::rv_policy::reference, "The attribute as a set, or none if it is another kind (Rust has no `as_set`; it matches\n`GenericAttributeKind::GenericAttributeSet`).");
}

} 