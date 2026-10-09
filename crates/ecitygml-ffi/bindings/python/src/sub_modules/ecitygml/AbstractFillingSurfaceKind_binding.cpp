#include "diplomat_nanobind_common.hpp"


#include "AbstractFillingSurfaceKind.hpp"

namespace ecitygml {
void add_AbstractFillingSurfaceKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractFillingSurfaceKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractFillingSurfaceKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractFillingSurfaceKind> opaque(mod, "AbstractFillingSurfaceKind", nb::type_slots(ecitygml_AbstractFillingSurfaceKind_slots), "A filling surface (door or window surface), borrowed from a city model. It has the getters of\nevery ancestor, like the concrete types; `feature_type()` tells which one it is.");
    opaque
        .def("bounded_by", &ecitygml::AbstractFillingSurfaceKind::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::AbstractFillingSurfaceKind::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AbstractFillingSurfaceKind::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AbstractFillingSurfaceKind::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("feature_type", &ecitygml::AbstractFillingSurfaceKind::feature_type)
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AbstractFillingSurfaceKind::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AbstractFillingSurfaceKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::AbstractFillingSurfaceKind::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::AbstractFillingSurfaceKind::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::AbstractFillingSurfaceKind::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::AbstractFillingSurfaceKind::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::AbstractFillingSurfaceKind::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractFillingSurfaceKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AbstractFillingSurfaceKind::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AbstractFillingSurfaceKind::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AbstractFillingSurfaceKind::relative_to_water)
        .def("termination_date", &ecitygml::AbstractFillingSurfaceKind::termination_date, nb::rv_policy::reference_internal)
        .def("valid_from", &ecitygml::AbstractFillingSurfaceKind::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AbstractFillingSurfaceKind::valid_to, nb::rv_policy::reference_internal);
}

} 