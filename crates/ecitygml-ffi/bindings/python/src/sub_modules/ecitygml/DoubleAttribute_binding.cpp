#include "diplomat_nanobind_common.hpp"


#include "DoubleAttribute.hpp"

namespace ecitygml {
void add_DoubleAttribute_binding(nb::module_ mod) {
    PyType_Slot ecitygml_DoubleAttribute_slots[] = {
        {Py_tp_free, (void *)ecitygml::DoubleAttribute::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::DoubleAttribute> opaque(mod, "DoubleAttribute", nb::type_slots(ecitygml_DoubleAttribute_slots), "A generic attribute with a floating-point value, borrowed from a city model.");
    opaque
        .def("name", &ecitygml::DoubleAttribute::name)
        .def("value", &ecitygml::DoubleAttribute::value);
}

} 