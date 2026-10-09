#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "PlantCover.hpp"

namespace ecitygml {
void add_PlantCover_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PlantCover_slots[] = {
        {Py_tp_free, (void *)ecitygml::PlantCover::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PlantCover> opaque(mod, "PlantCover", nb::type_slots(ecitygml_PlantCover_slots), "A plant cover (an area covered by vegetation), borrowed from a city model.");
    opaque
        .def("average_height", &ecitygml::PlantCover::average_height, nb::rv_policy::reference_internal)
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::PlantCover::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::PlantCover::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::PlantCover::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::PlantCover::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::PlantCover::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::PlantCover::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::PlantCover::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::PlantCover::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::PlantCover::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::PlantCover::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::PlantCover::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::PlantCover::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::PlantCover::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::PlantCover::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::PlantCover::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::PlantCover::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::PlantCover::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::PlantCover::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::PlantCover::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::PlantCover::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::PlantCover::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::PlantCover::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::PlantCover::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::PlantCover::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::PlantCover::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("max_height", &ecitygml::PlantCover::max_height, nb::rv_policy::reference_internal)
        .def("min_height", &ecitygml::PlantCover::min_height, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::PlantCover::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::PlantCover::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::PlantCover::relative_to_terrain)
        .def("relative_to_water", &ecitygml::PlantCover::relative_to_water)
        .def("space_type", &ecitygml::PlantCover::space_type)
        .def("termination_date", &ecitygml::PlantCover::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::PlantCover::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a plant cover, or none if it is another type (Rust: `<&PlantCover>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::PlantCover::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::PlantCover::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::PlantCover::valid_to, nb::rv_policy::reference_internal);
}

} 