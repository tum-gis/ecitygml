#include "diplomat_nanobind_common.hpp"


#include "OccupantTypeValue.hpp"

namespace ecitygml {
void add_OccupantTypeValue_binding(nb::module_ mod) {
    PyType_Slot ecitygml_OccupantTypeValue_slots[] = {
        {Py_tp_free, (void *)ecitygml::OccupantTypeValue::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::OccupantTypeValue> opaque(mod, "OccupantTypeValue", nb::type_slots(ecitygml_OccupantTypeValue_slots), "The `occupantType` property of an Occupancy.");
    opaque
        .def("code", &ecitygml::OccupantTypeValue::code, nb::rv_policy::reference_internal)
        .def("value", &ecitygml::OccupantTypeValue::value);
}

} 