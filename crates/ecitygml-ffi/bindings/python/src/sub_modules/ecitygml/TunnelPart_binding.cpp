#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "TunnelPart.hpp"

namespace ecitygml {
void add_TunnelPart_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelPart_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelPart::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelPart> opaque(mod, "TunnelPart", nb::type_slots(ecitygml_TunnelPart_slots), "A tunnel part, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::TunnelPart::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::TunnelPart::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::TunnelPart::creation_date, nb::rv_policy::reference_internal)
        .def("date_of_construction", &ecitygml::TunnelPart::date_of_construction, nb::rv_policy::reference_internal)
        .def("date_of_demolition", &ecitygml::TunnelPart::date_of_demolition, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::TunnelPart::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::generic_attributes)), nb::keep_alive<0, 1>())
        .def("heights", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::heights)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::TunnelPart::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::TunnelPart::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::TunnelPart::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::TunnelPart::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::TunnelPart::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::TunnelPart::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::TunnelPart::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::TunnelPart::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::TunnelPart::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::TunnelPart::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::TunnelPart::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::TunnelPart::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::TunnelPart::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::TunnelPart::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::TunnelPart::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::TunnelPart::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::TunnelPart::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::TunnelPart::relative_to_terrain)
        .def("relative_to_water", &ecitygml::TunnelPart::relative_to_water)
        .def("space_type", &ecitygml::TunnelPart::space_type)
        .def("termination_date", &ecitygml::TunnelPart::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::TunnelPart::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a tunnel part, or none if it is another type (Rust: `<&TunnelPart>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::TunnelPart::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::TunnelPart::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::TunnelPart::valid_to, nb::rv_policy::reference_internal);
}

} 