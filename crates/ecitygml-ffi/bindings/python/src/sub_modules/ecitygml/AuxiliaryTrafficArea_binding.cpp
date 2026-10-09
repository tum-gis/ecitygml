#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "AuxiliaryTrafficArea.hpp"

namespace ecitygml {
void add_AuxiliaryTrafficArea_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AuxiliaryTrafficArea_slots[] = {
        {Py_tp_free, (void *)ecitygml::AuxiliaryTrafficArea::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AuxiliaryTrafficArea> opaque(mod, "AuxiliaryTrafficArea", nb::type_slots(ecitygml_AuxiliaryTrafficArea_slots), "An auxiliary traffic area, borrowed from a city model.");
    opaque
        .def("bounded_by", &ecitygml::AuxiliaryTrafficArea::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::AuxiliaryTrafficArea::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::AuxiliaryTrafficArea::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AuxiliaryTrafficArea::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AuxiliaryTrafficArea::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::AuxiliaryTrafficArea::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::AuxiliaryTrafficArea::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::AuxiliaryTrafficArea::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::AuxiliaryTrafficArea::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::AuxiliaryTrafficArea::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AuxiliaryTrafficArea::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AuxiliaryTrafficArea::relative_to_water)
        .def("surface_material", &ecitygml::AuxiliaryTrafficArea::surface_material, nb::rv_policy::reference_internal)
        .def("termination_date", &ecitygml::AuxiliaryTrafficArea::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::AuxiliaryTrafficArea::try_from, "feature"_a, nb::rv_policy::reference, "The feature as an auxiliary traffic area, or none if it is another type (Rust: `<&AuxiliaryTrafficArea>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::AuxiliaryTrafficArea::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::AuxiliaryTrafficArea::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AuxiliaryTrafficArea::valid_to, nb::rv_policy::reference_internal);
}

} 