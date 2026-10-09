#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "SolitaryVegetationObject.hpp"

namespace ecitygml {
void add_SolitaryVegetationObject_binding(nb::module_ mod) {
    PyType_Slot ecitygml_SolitaryVegetationObject_slots[] = {
        {Py_tp_free, (void *)ecitygml::SolitaryVegetationObject::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::SolitaryVegetationObject> opaque(mod, "SolitaryVegetationObject", nb::type_slots(ecitygml_SolitaryVegetationObject_slots), "A solitary vegetation object (e.g. a tree), borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::SolitaryVegetationObject::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::SolitaryVegetationObject::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::SolitaryVegetationObject::creation_date, nb::rv_policy::reference_internal)
        .def("crown_diameter", &ecitygml::SolitaryVegetationObject::crown_diameter, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::SolitaryVegetationObject::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::generic_attributes)), nb::keep_alive<0, 1>())
        .def("height", &ecitygml::SolitaryVegetationObject::height, nb::rv_policy::reference_internal)
        .def("id", &ecitygml::SolitaryVegetationObject::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::SolitaryVegetationObject::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::SolitaryVegetationObject::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::SolitaryVegetationObject::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::SolitaryVegetationObject::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::SolitaryVegetationObject::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::SolitaryVegetationObject::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::SolitaryVegetationObject::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::SolitaryVegetationObject::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::SolitaryVegetationObject::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::SolitaryVegetationObject::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::SolitaryVegetationObject::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::SolitaryVegetationObject::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::SolitaryVegetationObject::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::SolitaryVegetationObject::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::SolitaryVegetationObject::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::SolitaryVegetationObject::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("max_root_ball_depth", &ecitygml::SolitaryVegetationObject::max_root_ball_depth, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::SolitaryVegetationObject::relative_to_terrain)
        .def("relative_to_water", &ecitygml::SolitaryVegetationObject::relative_to_water)
        .def("root_ball_diameter", &ecitygml::SolitaryVegetationObject::root_ball_diameter, nb::rv_policy::reference_internal)
        .def("space_type", &ecitygml::SolitaryVegetationObject::space_type)
        .def("species", &ecitygml::SolitaryVegetationObject::species, nb::rv_policy::reference_internal)
        .def("termination_date", &ecitygml::SolitaryVegetationObject::termination_date, nb::rv_policy::reference_internal)
        .def("trunk_diameter", &ecitygml::SolitaryVegetationObject::trunk_diameter, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::SolitaryVegetationObject::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a solitary vegetation object, or none if it is another type (Rust: `<&SolitaryVegetationObject>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::SolitaryVegetationObject::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::SolitaryVegetationObject::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::SolitaryVegetationObject::valid_to, nb::rv_policy::reference_internal);
}

} 