#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "BuildingPart.hpp"

namespace ecitygml {
void add_BuildingPart_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingPart_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingPart::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingPart> opaque(mod, "BuildingPart", nb::type_slots(ecitygml_BuildingPart_slots), "A building part, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::BuildingPart::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("building_subdivisions", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::building_subdivisions)), nb::keep_alive<0, 1>(), "The storeys and building units (`buildingSubdivision`).")
        .def("class_", &ecitygml::BuildingPart::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::BuildingPart::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::BuildingPart::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::BuildingPart::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::BuildingPart::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::BuildingPart::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::BuildingPart::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::BuildingPart::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::BuildingPart::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::BuildingPart::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::BuildingPart::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::BuildingPart::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::BuildingPart::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::BuildingPart::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::BuildingPart::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::BuildingPart::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::BuildingPart::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::BuildingPart::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::BuildingPart::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::BuildingPart::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::BuildingPart::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::BuildingPart::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::BuildingPart::relative_to_terrain)
        .def("relative_to_water", &ecitygml::BuildingPart::relative_to_water)
        .def("roof_type", &ecitygml::BuildingPart::roof_type, nb::rv_policy::reference_internal)
        .def("space_type", &ecitygml::BuildingPart::space_type)
        .def("storeys_above_ground", &ecitygml::BuildingPart::storeys_above_ground)
        .def("storeys_below_ground", &ecitygml::BuildingPart::storeys_below_ground)
        .def("termination_date", &ecitygml::BuildingPart::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::BuildingPart::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a building part, or none if it is another type (Rust: `<&BuildingPart>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::BuildingPart::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::BuildingPart::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::BuildingPart::valid_to, nb::rv_policy::reference_internal);
}

} 