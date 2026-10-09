#include "diplomat_nanobind_common.hpp"


#include "StringAttribute.hpp"

namespace ecitygml {
void add_StringAttribute_binding(nb::module_ mod) {
    PyType_Slot ecitygml_StringAttribute_slots[] = {
        {Py_tp_free, (void *)ecitygml::StringAttribute::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::StringAttribute> opaque(mod, "StringAttribute", nb::type_slots(ecitygml_StringAttribute_slots), "A generic attribute with a text value, borrowed from a city model.");
    opaque
        .def("name", &ecitygml::StringAttribute::name)
        .def("value", &ecitygml::StringAttribute::value);
}

} 