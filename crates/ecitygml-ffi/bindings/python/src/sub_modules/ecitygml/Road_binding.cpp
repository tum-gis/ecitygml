#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Road.hpp"

namespace ecitygml {
void add_Road_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Road_slots[] = {
        {Py_tp_free, (void *)ecitygml::Road::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Road> opaque(mod, "Road", nb::type_slots(ecitygml_Road_slots), "A road, borrowed from a city model.");
    opaque
        .def("auxiliary_traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Road::auxiliary_traffic_spaces)), nb::keep_alive<0, 1>())
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Road::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Road::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Road::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Road::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Road::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Road::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::Road::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Road::generic_attributes)), nb::keep_alive<0, 1>())
        .def("holes", std::move(maybe_op_unwrap(&ecitygml::Road::holes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Road::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("intersections", std::move(maybe_op_unwrap(&ecitygml::Road::intersections)), nb::keep_alive<0, 1>())
        .def("lod0_multi_curve", &ecitygml::Road::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Road::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Road::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Road::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Road::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Road::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Road::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Road::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Road::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Road::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Road::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Road::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Road::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("markings", std::move(maybe_op_unwrap(&ecitygml::Road::markings)), nb::keep_alive<0, 1>())
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Road::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Road::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Road::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Road::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Road::relative_to_water)
        .def("sections", std::move(maybe_op_unwrap(&ecitygml::Road::sections)), nb::keep_alive<0, 1>())
        .def("space_type", &ecitygml::Road::space_type)
        .def("termination_date", &ecitygml::Road::termination_date, nb::rv_policy::reference_internal)
        .def("traffic_direction", &ecitygml::Road::traffic_direction)
        .def("traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Road::traffic_spaces)), nb::keep_alive<0, 1>())
        .def_static("try_from", &ecitygml::Road::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a road, or none if it is another type (Rust: `<&Road>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::Road::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::Road::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Road::valid_to, nb::rv_policy::reference_internal);
}

} 