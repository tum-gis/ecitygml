#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "TrafficArea.hpp"

namespace ecitygml {
void add_TrafficArea_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficArea_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficArea::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficArea> opaque(mod, "TrafficArea", nb::type_slots(ecitygml_TrafficArea_slots), "A traffic area, borrowed from a city model.");
    opaque
        .def("bounded_by", &ecitygml::TrafficArea::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::TrafficArea::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::TrafficArea::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::TrafficArea::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("functions", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::functions)), nb::keep_alive<0, 1>())
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::TrafficArea::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::TrafficArea::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::TrafficArea::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::TrafficArea::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::TrafficArea::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::TrafficArea::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::TrafficArea::relative_to_terrain)
        .def("relative_to_water", &ecitygml::TrafficArea::relative_to_water)
        .def("surface_material", &ecitygml::TrafficArea::surface_material, nb::rv_policy::reference_internal)
        .def("termination_date", &ecitygml::TrafficArea::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::TrafficArea::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a traffic area, or none if it is another type (Rust: `<&TrafficArea>::try_from`).")
        .def("usages", std::move(maybe_op_unwrap(&ecitygml::TrafficArea::usages)), nb::keep_alive<0, 1>())
        .def("valid_from", &ecitygml::TrafficArea::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::TrafficArea::valid_to, nb::rv_policy::reference_internal);
}

} 