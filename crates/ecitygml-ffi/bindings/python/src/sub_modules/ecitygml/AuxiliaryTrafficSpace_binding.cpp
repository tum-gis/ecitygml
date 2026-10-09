#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "AuxiliaryTrafficSpace.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficSpace_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficSpace_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficSpace::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficSpace> opaque(mod, "AuxiliaryTrafficSpace", nb::type_slots(ecitygml_AuxiliaryTrafficSpace_slots), "An auxiliary traffic space, borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::AuxiliaryTrafficSpace::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::AuxiliaryTrafficSpace::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::AuxiliaryTrafficSpace::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AuxiliaryTrafficSpace::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::generic_attributes)), nb::keep_alive<0, 1>())
        .def("granularity", &ecitygml::AuxiliaryTrafficSpace::granularity, "Returned by value (Rust: `&GranularityValue`), as Diplomat enums are values.")
        .def("id", &ecitygml::AuxiliaryTrafficSpace::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::AuxiliaryTrafficSpace::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::AuxiliaryTrafficSpace::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::AuxiliaryTrafficSpace::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::AuxiliaryTrafficSpace::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::AuxiliaryTrafficSpace::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::AuxiliaryTrafficSpace::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::AuxiliaryTrafficSpace::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::AuxiliaryTrafficSpace::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::AuxiliaryTrafficSpace::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::AuxiliaryTrafficSpace::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::AuxiliaryTrafficSpace::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::AuxiliaryTrafficSpace::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::AuxiliaryTrafficSpace::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AuxiliaryTrafficSpace::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AuxiliaryTrafficSpace::relative_to_water)
        .def("space_type", &ecitygml::AuxiliaryTrafficSpace::space_type)
        .def("termination_date", &ecitygml::AuxiliaryTrafficSpace::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::AuxiliaryTrafficSpace::try_from, "feature"_a, nb::rv_policy::reference, "The feature as an auxiliary traffic space, or none if it is another type (Rust: `<&AuxiliaryTrafficSpace>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficSpace::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::AuxiliaryTrafficSpace::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AuxiliaryTrafficSpace::valid_to, nb::rv_policy::reference_internal);
}

} 