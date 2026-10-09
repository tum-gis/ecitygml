#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "BridgePart.hpp"

namespace ecitygml {
void add_BridgePart_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BridgePart_slots[] = {
        {Py_tp_free, (void *)ecitygml::BridgePart::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BridgePart> opaque(mod, "BridgePart", nb::type_slots(ecitygml_BridgePart_slots), "A bridge part, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::BridgePart::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::BridgePart::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::BridgePart::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::BridgePart::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::BridgePart::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::BridgePart::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::BridgePart::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::BridgePart::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::BridgePart::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::BridgePart::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::BridgePart::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::BridgePart::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("is_movable", &ecitygml::BridgePart::is_movable, "Not in Kotlin: diplomat-tool 0.16's Kotlin backend generates invalid code for an\n`Option<bool>` return (`returnVal.option()? > 0`).")
        .def("lod0_multi_curve", &ecitygml::BridgePart::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::BridgePart::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::BridgePart::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::BridgePart::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::BridgePart::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::BridgePart::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::BridgePart::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::BridgePart::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::BridgePart::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::BridgePart::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::BridgePart::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::BridgePart::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::BridgePart::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::BridgePart::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::BridgePart::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::BridgePart::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::BridgePart::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::BridgePart::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::BridgePart::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::BridgePart::relative_to_terrain)
        .def("relative_to_water", &ecitygml::BridgePart::relative_to_water)
        .def("space_type", &ecitygml::BridgePart::space_type)
        .def("termination_date", &ecitygml::BridgePart::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::BridgePart::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a bridge part, or none if it is another type (Rust: `<&BridgePart>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::BridgePart::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::BridgePart::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::BridgePart::valid_to, nb::rv_policy::reference_internal);
}

} 