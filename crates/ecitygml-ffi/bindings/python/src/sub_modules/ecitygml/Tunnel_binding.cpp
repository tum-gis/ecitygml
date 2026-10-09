#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Tunnel.hpp"

namespace ecitygml {
void add_Tunnel_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Tunnel_slots[] = {
        {Py_tp_free, (void *)ecitygml::Tunnel::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Tunnel> opaque(mod, "Tunnel", nb::type_slots(ecitygml_Tunnel_slots), "A tunnel, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Tunnel::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Tunnel::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Tunnel::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Tunnel::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::Tunnel::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::Tunnel::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Tunnel::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Tunnel::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::Tunnel::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Tunnel::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::Tunnel::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Tunnel::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Tunnel::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Tunnel::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Tunnel::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::Tunnel::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Tunnel::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Tunnel::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::Tunnel::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Tunnel::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Tunnel::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Tunnel::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Tunnel::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::Tunnel::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Tunnel::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Tunnel::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Tunnel::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Tunnel::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Tunnel::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Tunnel::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Tunnel::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Tunnel::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Tunnel::relative_to_water)
        .def("space_type", &ecitygml::Tunnel::space_type)
        .def("termination_date", &ecitygml::Tunnel::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Tunnel::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a tunnel, or none if it is another type (Rust: `<&Tunnel>::try_from`).")
        .def("tunnel_parts", std::move(maybe_op_unwrap(&ecitygml::Tunnel::tunnel_parts)), nb::keep_alive<0, 1>())
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::Tunnel::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::Tunnel::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Tunnel::valid_to, nb::rv_policy::reference_internal);
}

} 