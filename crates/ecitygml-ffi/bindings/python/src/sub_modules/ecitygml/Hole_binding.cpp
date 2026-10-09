#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Hole.hpp"

namespace ecitygml {
void add_Hole_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Hole_slots[] = {
        {Py_tp_free, (void *)ecitygml::Hole::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Hole> opaque(mod, "Hole", nb::type_slots(ecitygml_Hole_slots), "A hole, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Hole::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Hole::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Hole::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Hole::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Hole::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Hole::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Hole::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Hole::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Hole::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Hole::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Hole::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Hole::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Hole::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Hole::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Hole::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Hole::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Hole::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Hole::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Hole::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Hole::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Hole::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Hole::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Hole::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Hole::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Hole::relative_to_water)
        .def("space_type", &ecitygml::Hole::space_type)
        .def("termination_date", &ecitygml::Hole::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Hole::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a hole, or none if it is another type (Rust: `<&Hole>::try_from`).")
        .def("valid_from", &ecitygml::Hole::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Hole::valid_to, nb::rv_policy::reference_internal);
}

} 