#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Bridge.hpp"

namespace ecitygml {
void add_Bridge_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Bridge_slots[] = {
        {Py_tp_free, (void *)ecitygml::Bridge::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Bridge> opaque(mod, "Bridge", nb::type_slots(ecitygml_Bridge_slots), "A bridge, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Bridge::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Bridge::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("bridge_parts", std::move(maybe_op_unwrap(&ecitygml::Bridge::bridge_parts)), nb::keep_alive<0, 1>())
        .def("class_", &ecitygml::Bridge::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Bridge::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::Bridge::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::Bridge::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Bridge::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Bridge::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::Bridge::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Bridge::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::Bridge::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Bridge::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("is_movable", &ecitygml::Bridge::is_movable, "Not in Kotlin: diplomat-tool 0.16's Kotlin backend generates invalid code for an\n`Option<bool>` return (`returnVal.option()? > 0`).")
        .def("lod0_multi_curve", &ecitygml::Bridge::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Bridge::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Bridge::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::Bridge::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Bridge::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Bridge::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::Bridge::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Bridge::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Bridge::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Bridge::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Bridge::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::Bridge::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Bridge::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Bridge::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Bridge::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Bridge::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Bridge::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Bridge::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Bridge::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Bridge::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Bridge::relative_to_water)
        .def("space_type", &ecitygml::Bridge::space_type)
        .def("termination_date", &ecitygml::Bridge::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Bridge::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a bridge, or none if it is another type (Rust: `<&Bridge>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::Bridge::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::Bridge::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Bridge::valid_to, nb::rv_policy::reference_internal);
}

} 