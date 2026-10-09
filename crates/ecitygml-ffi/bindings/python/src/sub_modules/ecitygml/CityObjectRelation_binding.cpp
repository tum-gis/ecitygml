#include "diplomat_nanobind_common.hpp"


#include "CityObjectRelation.hpp"

namespace ecitygml {
void add_CityObjectRelation_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityObjectRelation_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityObjectRelation::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityObjectRelation> opaque(mod, "CityObjectRelation", nb::type_slots(ecitygml_CityObjectRelation_slots), "A relation of a city object to another one, borrowed from a city model.");
    opaque
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::CityObjectRelation::generic_attributes)), nb::keep_alive<0, 1>())
        .def("relation_to", &ecitygml::CityObjectRelation::relation_to, nb::rv_policy::reference_internal, "The related city object (`relatedTo`), by reference.")
        .def("relation_type", &ecitygml::CityObjectRelation::relation_type, nb::rv_policy::reference_internal);
}

} 