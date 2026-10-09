#include "diplomat_nanobind_common.hpp"


#include "IntAttribute.hpp"

namespace ecitygml {
void add_IntAttribute_binding(nb::module_ mod) {
    PyType_Slot ecitygml_IntAttribute_slots[] = {
        {Py_tp_free, (void *)ecitygml::IntAttribute::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::IntAttribute> opaque(mod, "IntAttribute", nb::type_slots(ecitygml_IntAttribute_slots), "A generic attribute with an integer value, borrowed from a city model.");
    opaque
        .def("name", &ecitygml::IntAttribute::name)
        .def("value", &ecitygml::IntAttribute::value);
}

} 