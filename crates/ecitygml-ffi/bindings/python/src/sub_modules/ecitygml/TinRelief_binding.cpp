#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "TinRelief.hpp"

namespace ecitygml {
void add_TinRelief_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TinRelief_slots[] = {
        {Py_tp_free, (void *)ecitygml::TinRelief::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TinRelief> opaque(mod, "TinRelief", nb::type_slots(ecitygml_TinRelief_slots), "A relief component given as a triangulated irregular network, borrowed from a city model.");
    opaque
        .def("bounded_by", &ecitygml::TinRelief::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::TinRelief::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::TinRelief::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::TinRelief::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::TinRelief::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::TinRelief::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod", &ecitygml::TinRelief::lod)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::TinRelief::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::TinRelief::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::TinRelief::relative_to_terrain)
        .def("relative_to_water", &ecitygml::TinRelief::relative_to_water)
        .def("termination_date", &ecitygml::TinRelief::termination_date, nb::rv_policy::reference_internal)
        .def("tin", &ecitygml::TinRelief::tin, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::TinRelief::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a tin relief, or none if it is another type (Rust: `<&TinRelief>::try_from`).")
        .def("valid_from", &ecitygml::TinRelief::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::TinRelief::valid_to, nb::rv_policy::reference_internal);
}

} 