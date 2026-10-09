#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Intersection.hpp"

namespace ecitygml {
void add_Intersection_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Intersection_slots[] = {
        {Py_tp_free, (void *)ecitygml::Intersection::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Intersection> opaque(mod, "Intersection", nb::type_slots(ecitygml_Intersection_slots), "A intersection, borrowed from a city model.");
    opaque
        .def("auxiliary_traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Intersection::auxiliary_traffic_spaces)), nb::keep_alive<0, 1>())
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Intersection::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Intersection::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Intersection::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Intersection::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Intersection::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Intersection::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Intersection::generic_attributes)), nb::keep_alive<0, 1>())
        .def("holes", std::move(maybe_op_unwrap(&ecitygml::Intersection::holes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Intersection::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Intersection::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Intersection::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Intersection::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Intersection::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Intersection::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Intersection::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Intersection::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Intersection::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Intersection::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Intersection::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Intersection::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Intersection::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Intersection::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("markings", std::move(maybe_op_unwrap(&ecitygml::Intersection::markings)), nb::keep_alive<0, 1>())
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Intersection::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Intersection::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Intersection::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Intersection::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Intersection::relative_to_water)
        .def("space_type", &ecitygml::Intersection::space_type)
        .def("termination_date", &ecitygml::Intersection::termination_date, nb::rv_policy::reference_internal)
        .def("traffic_direction", &ecitygml::Intersection::traffic_direction)
        .def("traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Intersection::traffic_spaces)), nb::keep_alive<0, 1>())
        .def_static("try_from", &ecitygml::Intersection::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a intersection, or none if it is another type (Rust: `<&Intersection>::try_from`).")
        .def("valid_from", &ecitygml::Intersection::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Intersection::valid_to, nb::rv_policy::reference_internal);
}

} 