#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "BuildingUnit.hpp"

namespace ecitygml {
void add_BuildingUnit_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingUnit_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingUnit::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingUnit> opaque(mod, "BuildingUnit", nb::type_slots(ecitygml_BuildingUnit_slots), "A building unit, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::BuildingUnit::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::BuildingUnit::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::BuildingUnit::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::BuildingUnit::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::BuildingUnit::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::BuildingUnit::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::BuildingUnit::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::BuildingUnit::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::BuildingUnit::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::BuildingUnit::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::BuildingUnit::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::BuildingUnit::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::BuildingUnit::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::BuildingUnit::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::BuildingUnit::lod3_solid, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::BuildingUnit::relative_to_terrain)
        .def("relative_to_water", &ecitygml::BuildingUnit::relative_to_water)
        .def("space_type", &ecitygml::BuildingUnit::space_type)
        .def("termination_date", &ecitygml::BuildingUnit::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::BuildingUnit::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a building unit, or none if it is another type (Rust: `<&BuildingUnit>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::BuildingUnit::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::BuildingUnit::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::BuildingUnit::valid_to, nb::rv_policy::reference_internal);
}

} 