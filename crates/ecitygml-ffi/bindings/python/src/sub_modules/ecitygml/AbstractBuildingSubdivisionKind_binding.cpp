#include "diplomat_nanobind_common.hpp"


#include "AbstractBuildingSubdivisionKind.hpp"

namespace ecitygml {
void add_AbstractBuildingSubdivisionKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractBuildingSubdivisionKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractBuildingSubdivisionKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractBuildingSubdivisionKind> opaque(mod, "AbstractBuildingSubdivisionKind", nb::type_slots(ecitygml_AbstractBuildingSubdivisionKind_slots), "A building subdivision (storey or building unit), borrowed from a city model. It has the\ngetters of every ancestor, like the concrete types, which add none; `feature_type()` tells\nwhich one it is.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::AbstractBuildingSubdivisionKind::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::AbstractBuildingSubdivisionKind::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::AbstractBuildingSubdivisionKind::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AbstractBuildingSubdivisionKind::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("feature_type", &ecitygml::AbstractBuildingSubdivisionKind::feature_type)
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AbstractBuildingSubdivisionKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::AbstractBuildingSubdivisionKind::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::AbstractBuildingSubdivisionKind::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::AbstractBuildingSubdivisionKind::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::AbstractBuildingSubdivisionKind::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::AbstractBuildingSubdivisionKind::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::AbstractBuildingSubdivisionKind::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::AbstractBuildingSubdivisionKind::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::AbstractBuildingSubdivisionKind::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::AbstractBuildingSubdivisionKind::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::AbstractBuildingSubdivisionKind::lod3_solid, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AbstractBuildingSubdivisionKind::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AbstractBuildingSubdivisionKind::relative_to_water)
        .def("space_type", &ecitygml::AbstractBuildingSubdivisionKind::space_type)
        .def("termination_date", &ecitygml::AbstractBuildingSubdivisionKind::termination_date, nb::rv_policy::reference_internal)
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::AbstractBuildingSubdivisionKind::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::AbstractBuildingSubdivisionKind::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AbstractBuildingSubdivisionKind::valid_to, nb::rv_policy::reference_internal);
}

} 