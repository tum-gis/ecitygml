#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Building.hpp"

namespace ecitygml {
void add_Building_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Building_slots[] = {
        {Py_tp_free, (void *)ecitygml::Building::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Building> opaque(mod, "Building", nb::type_slots(ecitygml_Building_slots), "A building, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Building::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Building::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("building_parts", std::move(maybe_op_unwrap(&ecitygml::Building::building_parts)), nb::keep_alive<0, 1>())
        .def("building_subdivisions", std::move(maybe_op_unwrap(&ecitygml::Building::building_subdivisions)), nb::keep_alive<0, 1>(), "The storeys and building units (`buildingSubdivision`).")
        .def("class_", &ecitygml::Building::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Building::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::Building::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::Building::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Building::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Building::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::Building::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Building::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::Building::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Building::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Building::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Building::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Building::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::Building::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Building::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Building::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::Building::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Building::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Building::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Building::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Building::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::Building::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Building::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Building::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Building::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Building::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Building::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Building::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Building::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Building::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Building::relative_to_water)
        .def("roof_type", &ecitygml::Building::roof_type, nb::rv_policy::reference_internal)
        .def("space_type", &ecitygml::Building::space_type)
        .def("storeys_above_ground", &ecitygml::Building::storeys_above_ground)
        .def("storeys_below_ground", &ecitygml::Building::storeys_below_ground)
        .def("termination_date", &ecitygml::Building::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Building::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a building, or none if it is another type (Rust: `<&Building>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::Building::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::Building::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Building::valid_to, nb::rv_policy::reference_internal);
}

} 