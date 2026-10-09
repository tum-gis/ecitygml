#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "CityFurniture.hpp"

namespace ecitygml {
void add_CityFurniture_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityFurniture_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityFurniture::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityFurniture> opaque(mod, "CityFurniture", nb::type_slots(ecitygml_CityFurniture_slots), "A city furniture object (e.g. a traffic sign or bench), borrowed from a city model.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::CityFurniture::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::CityFurniture::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::CityFurniture::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::CityFurniture::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::CityFurniture::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::CityFurniture::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::CityFurniture::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::CityFurniture::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_implicit_representation", &ecitygml::CityFurniture::lod1_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::CityFurniture::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod1_terrain_intersection_curve", &ecitygml::CityFurniture::lod1_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod2_implicit_representation", &ecitygml::CityFurniture::lod2_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::CityFurniture::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::CityFurniture::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::CityFurniture::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod2_terrain_intersection_curve", &ecitygml::CityFurniture::lod2_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("lod3_implicit_representation", &ecitygml::CityFurniture::lod3_implicit_representation, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::CityFurniture::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::CityFurniture::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::CityFurniture::lod3_solid, nb::rv_policy::reference_internal)
        .def("lod3_terrain_intersection_curve", &ecitygml::CityFurniture::lod3_terrain_intersection_curve, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::CityFurniture::relative_to_terrain)
        .def("relative_to_water", &ecitygml::CityFurniture::relative_to_water)
        .def("space_type", &ecitygml::CityFurniture::space_type)
        .def("termination_date", &ecitygml::CityFurniture::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::CityFurniture::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a city furniture, or none if it is another type (Rust: `<&CityFurniture>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::CityFurniture::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::CityFurniture::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::CityFurniture::valid_to, nb::rv_policy::reference_internal);
}

} 