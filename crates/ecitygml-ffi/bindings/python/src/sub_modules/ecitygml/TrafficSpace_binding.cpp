#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "TrafficSpace.hpp"

namespace ecitygml {
void add_TrafficSpace_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpace_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpace::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpace> opaque(mod, "TrafficSpace", nb::type_slots(ecitygml_TrafficSpace_slots), "A traffic space, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::TrafficSpace::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::TrafficSpace::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::TrafficSpace::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::TrafficSpace::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::generic_attributes)), nb::keep_alive<0, 1>())
        .def("granularity", &ecitygml::TrafficSpace::granularity, "Returned by value (Rust: `&GranularityValue`), as Diplomat enums are values.")
        .def("id", &ecitygml::TrafficSpace::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::TrafficSpace::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::TrafficSpace::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::TrafficSpace::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::TrafficSpace::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::TrafficSpace::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::TrafficSpace::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::TrafficSpace::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::TrafficSpace::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::TrafficSpace::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::TrafficSpace::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::TrafficSpace::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::TrafficSpace::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::TrafficSpace::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::occupancies)), nb::keep_alive<0, 1>())
        .def("predecessors", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::predecessors)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::TrafficSpace::relative_to_terrain)
        .def("relative_to_water", &ecitygml::TrafficSpace::relative_to_water)
        .def("space_type", &ecitygml::TrafficSpace::space_type)
        .def("successors", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::successors)), nb::keep_alive<0, 1>())
        .def("termination_date", &ecitygml::TrafficSpace::termination_date, nb::rv_policy::reference_internal)
        .def("traffic_direction", &ecitygml::TrafficSpace::traffic_direction)
        .def_static("try_from", &ecitygml::TrafficSpace::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a traffic space, or none if it is another type (Rust: `<&TrafficSpace>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::TrafficSpace::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::TrafficSpace::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::TrafficSpace::valid_to, nb::rv_policy::reference_internal);
}

} 