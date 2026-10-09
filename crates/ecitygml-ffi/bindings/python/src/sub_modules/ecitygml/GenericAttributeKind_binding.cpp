#include "diplomat_nanobind_common.hpp"


#include "GenericAttributeKind.hpp"

namespace ecitygml {
void add_GenericAttributeKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_GenericAttributeKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::GenericAttributeKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::GenericAttributeKind> opaque(mod, "GenericAttributeKind", nb::type_slots(ecitygml_GenericAttributeKind_slots), "A generic attribute of any kind, borrowed from a city model; get its value with `as_string`,\n`as_int`, `as_double`, `MeasureAttribute::try_from` or `GenericAttributeSet::try_from`.");
    opaque
        .def("as_double", &ecitygml::GenericAttributeKind::as_double, nb::rv_policy::reference_internal)
        .def("as_int", &ecitygml::GenericAttributeKind::as_int, nb::rv_policy::reference_internal)
        .def("as_string", &ecitygml::GenericAttributeKind::as_string, nb::rv_policy::reference_internal)
        .def("name", &ecitygml::GenericAttributeKind::name);
}

} 