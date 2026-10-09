#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "ReliefFeature.hpp"

namespace ecitygml {
void add_ReliefFeature_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ReliefFeature_slots[] = {
        {Py_tp_free, (void *)ecitygml::ReliefFeature::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ReliefFeature> opaque(mod, "ReliefFeature", nb::type_slots(ecitygml_ReliefFeature_slots), "A relief (terrain) feature made of relief components, borrowed from a city model.");
    opaque
        .def("bounded_by", &ecitygml::ReliefFeature::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::ReliefFeature::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::ReliefFeature::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::ReliefFeature::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::ReliefFeature::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::ReliefFeature::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod", &ecitygml::ReliefFeature::lod)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::ReliefFeature::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::ReliefFeature::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::ReliefFeature::relative_to_terrain)
        .def("relative_to_water", &ecitygml::ReliefFeature::relative_to_water)
        .def("relief_components", std::move(maybe_op_unwrap(&ecitygml::ReliefFeature::relief_components)), nb::keep_alive<0, 1>())
        .def("termination_date", &ecitygml::ReliefFeature::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::ReliefFeature::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a relief feature, or none if it is another type (Rust: `<&ReliefFeature>::try_from`).")
        .def("valid_from", &ecitygml::ReliefFeature::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::ReliefFeature::valid_to, nb::rv_policy::reference_internal);
}

} 