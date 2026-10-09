#include "diplomat_nanobind_common.hpp"


#include "ElevationReferenceValue.hpp"

namespace ecitygml {
void add_ElevationReferenceValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ElevationReferenceValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::ElevationReferenceValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ElevationReferenceValue> opaque(mod, "ElevationReferenceValue", nb::type_slots(ecitygml_ElevationReferenceValue_slots), "The `highReference`/`lowReference` property of a Height.");
    opaque
        .def("code", &ecitygml::ElevationReferenceValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::ElevationReferenceValue::value);
}

} 