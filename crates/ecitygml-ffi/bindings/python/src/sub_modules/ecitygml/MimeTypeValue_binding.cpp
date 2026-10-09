#include "diplomat_nanobind_common.hpp"


#include "MimeTypeValue.hpp"

namespace ecitygml {
void add_MimeTypeValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MimeTypeValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::MimeTypeValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MimeTypeValue> opaque(mod, "MimeTypeValue", nb::type_slots(ecitygml_MimeTypeValue_slots), "The `mimeType` property of an ImplicitGeometry.");
    opaque
        .def("code", &ecitygml::MimeTypeValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::MimeTypeValue::value);
}

} 