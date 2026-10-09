#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "GroundSurface.hpp"

namespace ecitygml {
void add_GroundSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_GroundSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::GroundSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::GroundSurface> opaque(mod, "GroundSurface", nb::type_slots(ecitygml_GroundSurface_slots), "A ground surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("bounded_by", &ecitygml::GroundSurface::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::GroundSurface::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::GroundSurface::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::GroundSurface::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("filling_surfaces", std::move(maybe_op_unwrap(&ecitygml::GroundSurface::filling_surfaces)), nb::keep_alive<0, 1>(), "The door and window surfaces in this surface (`con:fillingSurface`).")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::GroundSurface::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::GroundSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::GroundSurface::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::GroundSurface::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::GroundSurface::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::GroundSurface::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::GroundSurface::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::GroundSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::GroundSurface::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::GroundSurface::relative_to_terrain)
        .def("relative_to_water", &ecitygml::GroundSurface::relative_to_water)
        .def("termination_date", &ecitygml::GroundSurface::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::GroundSurface::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a ground surface, or none if it is another type (Rust: `<&GroundSurface>::try_from`).")
        .def("valid_from", &ecitygml::GroundSurface::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::GroundSurface::valid_to, nb::rv_policy::reference_internal);
}

} 