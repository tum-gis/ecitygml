#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "WindowSurface.hpp"

namespace ecitygml {
void add_WindowSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_WindowSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::WindowSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::WindowSurface> opaque(mod, "WindowSurface", nb::type_slots(ecitygml_WindowSurface_slots), "A window surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("bounded_by", &ecitygml::WindowSurface::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::WindowSurface::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::WindowSurface::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::WindowSurface::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::WindowSurface::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::WindowSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::WindowSurface::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::WindowSurface::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::WindowSurface::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::WindowSurface::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::WindowSurface::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::WindowSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::WindowSurface::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::WindowSurface::relative_to_terrain)
        .def("relative_to_water", &ecitygml::WindowSurface::relative_to_water)
        .def("termination_date", &ecitygml::WindowSurface::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::WindowSurface::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a window surface, or none if it is another type (Rust: `<&WindowSurface>::try_from`).")
        .def("valid_from", &ecitygml::WindowSurface::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::WindowSurface::valid_to, nb::rv_policy::reference_internal);
}

} 