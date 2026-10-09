#include "diplomat_nanobind_common.hpp"


#include "RelationTypeValue.hpp"

namespace ecitygml {
void add_RelationTypeValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RelationTypeValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::RelationTypeValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RelationTypeValue> opaque(mod, "RelationTypeValue", nb::type_slots(ecitygml_RelationTypeValue_slots), "The `relationType` property of a CityObjectRelation.");
    opaque
        .def("code", &ecitygml::RelationTypeValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::RelationTypeValue::value);
}

} 