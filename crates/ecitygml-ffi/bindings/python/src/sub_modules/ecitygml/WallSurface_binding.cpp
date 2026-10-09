#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "WallSurface.hpp"

namespace ecitygml {
void add_WallSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_WallSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::WallSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::WallSurface> opaque(mod, "WallSurface", nb::type_slots(ecitygml_WallSurface_slots), "A wall surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("bounded_by", &ecitygml::WallSurface::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::WallSurface::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::WallSurface::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::WallSurface::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("filling_surfaces", std::move(maybe_op_unwrap(&ecitygml::WallSurface::filling_surfaces)), nb::keep_alive<0, 1>(), "The door and window surfaces in this surface (`con:fillingSurface`).")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::WallSurface::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::WallSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::WallSurface::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::WallSurface::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::WallSurface::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::WallSurface::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::WallSurface::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::WallSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::WallSurface::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::WallSurface::relative_to_terrain)
        .def("relative_to_water", &ecitygml::WallSurface::relative_to_water)
        .def("termination_date", &ecitygml::WallSurface::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::WallSurface::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a wall surface, or none if it is another type (Rust: `<&WallSurface>::try_from`).")
        .def("valid_from", &ecitygml::WallSurface::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::WallSurface::valid_to, nb::rv_policy::reference_internal);
}

} 