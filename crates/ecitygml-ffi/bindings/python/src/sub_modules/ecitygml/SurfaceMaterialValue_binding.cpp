#include "diplomat_nanobind_common.hpp"


#include "SurfaceMaterialValue.hpp"

namespace ecitygml {
void add_SurfaceMaterialValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SurfaceMaterialValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::SurfaceMaterialValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SurfaceMaterialValue> opaque(mod, "SurfaceMaterialValue", nb::type_slots(ecitygml_SurfaceMaterialValue_slots), "The `surfaceMaterial` property of a TrafficArea or AuxiliaryTrafficArea.");
    opaque
        .def("code", &ecitygml::SurfaceMaterialValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::SurfaceMaterialValue::value);
}

} 