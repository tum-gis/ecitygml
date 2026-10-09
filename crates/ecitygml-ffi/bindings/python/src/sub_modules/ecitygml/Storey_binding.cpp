#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Storey.hpp"

namespace ecitygml {
void add_Storey_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Storey_slots[] = {
        {Py_tp_free, (void *)ecitygml::Storey::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Storey> opaque(mod, "Storey", nb::type_slots(ecitygml_Storey_slots), "A storey, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("boundaries", std::move(maybe_op_unwrap(&ecitygml::Storey::boundaries)), nb::keep_alive<0, 1>(), "The space's boundaries (e.g. wall surfaces or traffic areas).")
        .def("bounded_by", &ecitygml::Storey::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Storey::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Storey::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Storey::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Storey::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::Storey::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Storey::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Storey::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Storey::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Storey::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod0_point", &ecitygml::Storey::lod0_point, nb::rv_policy::reference_internal)
        .def("lod1_solid", &ecitygml::Storey::lod1_solid, nb::rv_policy::reference_internal)
        .def("lod2_multi_curve", &ecitygml::Storey::lod2_multi_curve, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Storey::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_solid", &ecitygml::Storey::lod2_solid, nb::rv_policy::reference_internal)
        .def("lod3_multi_curve", &ecitygml::Storey::lod3_multi_curve, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Storey::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_solid", &ecitygml::Storey::lod3_solid, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Storey::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Storey::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Storey::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Storey::relative_to_water)
        .def("space_type", &ecitygml::Storey::space_type)
        .def("termination_date", &ecitygml::Storey::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Storey::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a storey, or none if it is another type (Rust: `<&Storey>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::Storey::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::Storey::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Storey::valid_to, nb::rv_policy::reference_internal);
}

} 