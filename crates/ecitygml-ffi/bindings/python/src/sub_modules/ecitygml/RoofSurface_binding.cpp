#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "RoofSurface.hpp"

namespace ecitygml {
void add_RoofSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_RoofSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::RoofSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::RoofSurface> opaque(mod, "RoofSurface", nb::type_slots(ecitygml_RoofSurface_slots), "A roof surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("bounded_by", &ecitygml::RoofSurface::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::RoofSurface::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::RoofSurface::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::RoofSurface::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("filling_surfaces", std::move(maybe_op_unwrap(&ecitygml::RoofSurface::filling_surfaces)), nb::keep_alive<0, 1>(), "The door and window surfaces in this surface (`con:fillingSurface`).")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::RoofSurface::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::RoofSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::RoofSurface::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::RoofSurface::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::RoofSurface::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::RoofSurface::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::RoofSurface::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::RoofSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::RoofSurface::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::RoofSurface::relative_to_terrain)
        .def("relative_to_water", &ecitygml::RoofSurface::relative_to_water)
        .def("termination_date", &ecitygml::RoofSurface::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::RoofSurface::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a roof surface, or none if it is another type (Rust: `<&RoofSurface>::try_from`).")
        .def("valid_from", &ecitygml::RoofSurface::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::RoofSurface::valid_to, nb::rv_policy::reference_internal);
}

} 