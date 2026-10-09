#include "diplomat_nanobind_common.hpp"


#include "AbstractSpaceBoundaryKind.hpp"

namespace ecitygml {
void add_AbstractSpaceBoundaryKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSpaceBoundaryKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSpaceBoundaryKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSpaceBoundaryKind> opaque(mod, "AbstractSpaceBoundaryKind", nb::type_slots(ecitygml_AbstractSpaceBoundaryKind_slots), "A space boundary of any type (e.g. a wall surface or traffic area), borrowed from a city model.\nIt has the getters of every ancestor; for the concrete type, convert it with\n`AbstractFeatureKindRef::from_space_boundary` and e.g. `WallSurface::try_from`.");
    opaque
        .def("bounded_by", &ecitygml::AbstractSpaceBoundaryKind::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::AbstractSpaceBoundaryKind::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AbstractSpaceBoundaryKind::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AbstractSpaceBoundaryKind::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("feature_type", &ecitygml::AbstractSpaceBoundaryKind::feature_type)
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AbstractSpaceBoundaryKind::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AbstractSpaceBoundaryKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractSpaceBoundaryKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AbstractSpaceBoundaryKind::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AbstractSpaceBoundaryKind::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AbstractSpaceBoundaryKind::relative_to_water)
        .def("termination_date", &ecitygml::AbstractSpaceBoundaryKind::termination_date, nb::rv_policy::reference_internal)
        .def("valid_from", &ecitygml::AbstractSpaceBoundaryKind::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AbstractSpaceBoundaryKind::valid_to, nb::rv_policy::reference_internal);
}

} 