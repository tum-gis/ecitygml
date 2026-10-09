#include "diplomat_nanobind_common.hpp"


#include "Occupancy.hpp"

namespace ecitygml {
void add_Occupancy_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Occupancy_slots[] = {
        {Py_tp_free, (void *)ecitygml::Occupancy::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Occupancy> opaque(mod, "Occupancy", nb::type_slots(ecitygml_Occupancy_slots), "The number of occupants of a feature, borrowed from a city model.");
    opaque
        .def("interval", &ecitygml::Occupancy::interval, nb::rv_policy::reference_internal)
        .def("number_of_occupants", &ecitygml::Occupancy::number_of_occupants)
        .def("occupant_type", &ecitygml::Occupancy::occupant_type, nb::rv_policy::reference_internal);
}

} 