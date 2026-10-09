#include "diplomat_nanobind_common.hpp"


#include "AbstractReliefComponentKind.hpp"

namespace ecitygml {
void add_AbstractReliefComponentKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractReliefComponentKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractReliefComponentKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractReliefComponentKind> opaque(mod, "AbstractReliefComponentKind", nb::type_slots(ecitygml_AbstractReliefComponentKind_slots), "A relief component (a TIN relief), borrowed from a city model. It has the getters of every\nancestor; `feature_type()` tells which component it is. Not bound yet: the concrete types'\nown getters (e.g. `tin`); get a `TinRelief` from the features with `TinRelief::try_from`.");
    opaque
        .def("bounded_by", &ecitygml::AbstractReliefComponentKind::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::AbstractReliefComponentKind::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AbstractReliefComponentKind::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AbstractReliefComponentKind::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("feature_type", &ecitygml::AbstractReliefComponentKind::feature_type)
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AbstractReliefComponentKind::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AbstractReliefComponentKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod", &ecitygml::AbstractReliefComponentKind::lod)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractReliefComponentKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AbstractReliefComponentKind::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AbstractReliefComponentKind::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AbstractReliefComponentKind::relative_to_water)
        .def("termination_date", &ecitygml::AbstractReliefComponentKind::termination_date, nb::rv_policy::reference_internal)
        .def("valid_from", &ecitygml::AbstractReliefComponentKind::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AbstractReliefComponentKind::valid_to, nb::rv_policy::reference_internal);
}

} 