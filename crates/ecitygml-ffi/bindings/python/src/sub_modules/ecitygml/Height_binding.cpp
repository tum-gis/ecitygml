#include "diplomat_nanobind_common.hpp"


#include "Height.hpp"

namespace ecitygml {
void add_Height_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Height_slots[] = {
        {Py_tp_free, (void *)ecitygml::Height::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Height> opaque(mod, "Height", nb::type_slots(ecitygml_Height_slots), "A height of a construction between two reference levels, borrowed from a city model.");
    opaque
        .def("high_reference", &ecitygml::Height::high_reference, nb::rv_policy::reference_internal)
        .def("length", &ecitygml::Height::length, nb::rv_policy::reference_internal, "The height value (`con:value`).")
        .def("low_reference", &ecitygml::Height::low_reference, nb::rv_policy::reference_internal)
        .def("status", &ecitygml::Height::status);
}

} 