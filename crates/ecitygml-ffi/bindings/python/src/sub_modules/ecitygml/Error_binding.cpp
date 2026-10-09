#include "diplomat_nanobind_common.hpp"


#include "Error.hpp"

namespace ecitygml {
void add_Error_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Error_slots[] = {
        {Py_tp_free, (void *)ecitygml::Error::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Error> opaque(mod, "Error", nb::type_slots(ecitygml_Error_slots), "An error with its kind and a human-readable message.");
    opaque
        .def("kind", &ecitygml::Error::kind)
        .def("__str__", &ecitygml::Error::message);
}

} 