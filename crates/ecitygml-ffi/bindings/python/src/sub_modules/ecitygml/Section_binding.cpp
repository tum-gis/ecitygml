#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Section.hpp"

namespace ecitygml {
void add_Section_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Section_slots[] = {
        {Py_tp_free, (void *)ecitygml::Section::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Section> opaque(mod, "Section", nb::type_slots(ecitygml_Section_slots), "A section, borrowed from a city model.");
    opaque
        .def("auxiliary_traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Section::auxiliary_traffic_spaces)), nb::keep_alive<0, 1>())
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Section::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Section::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Section::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Section::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Section::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Section::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Section::generic_attributes)), nb::keep_alive<0, 1>())
        .def("holes", std::move(maybe_op_unwrap(&ecitygml::Section::holes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Section::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Section::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Section::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Section::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Section::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::Section::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Section::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Section::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Section::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::Section::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Section::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Section::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Section::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::Section::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("markings", std::move(maybe_op_unwrap(&ecitygml::Section::markings)), nb::keep_alive<0, 1>())
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Section::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("occupancies", std::move(maybe_op_unwrap(&ecitygml::Section::occupancies)), nb::keep_alive<0, 1>())
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Section::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Section::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Section::relative_to_water)
        .def("space_type", &ecitygml::Section::space_type)
        .def("termination_date", &ecitygml::Section::termination_date, nb::rv_policy::reference_internal)
        .def("traffic_direction", &ecitygml::Section::traffic_direction)
        .def("traffic_spaces", std::move(maybe_op_unwrap(&ecitygml::Section::traffic_spaces)), nb::keep_alive<0, 1>())
        .def_static("try_from", &ecitygml::Section::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a section, or none if it is another type (Rust: `<&Section>::try_from`).")
        .def("valid_from", &ecitygml::Section::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Section::valid_to, nb::rv_policy::reference_internal);
}

} 