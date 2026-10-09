#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "Marking.hpp"

namespace ecitygml {
void add_Marking_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Marking_slots[] = {
        {Py_tp_free, (void *)ecitygml::Marking::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Marking> opaque(mod, "Marking", nb::type_slots(ecitygml_Marking_slots), "A marking, borrowed from a city model.");
    opaque
        .def("bounded_by", &ecitygml::Marking::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("class_", &ecitygml::Marking::class_, nb::rv_policy::reference_internal)
        .def("creation_date", &ecitygml::Marking::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::Marking::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::Marking::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::Marking::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::Marking::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::Marking::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::Marking::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::Marking::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::Marking::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::Marking::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Marking::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::Marking::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::Marking::relative_to_terrain)
        .def("relative_to_water", &ecitygml::Marking::relative_to_water)
        .def("termination_date", &ecitygml::Marking::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::Marking::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a marking, or none if it is another type (Rust: `<&Marking>::try_from`).")
        .def("valid_from", &ecitygml::Marking::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::Marking::valid_to, nb::rv_policy::reference_internal);
}

} 