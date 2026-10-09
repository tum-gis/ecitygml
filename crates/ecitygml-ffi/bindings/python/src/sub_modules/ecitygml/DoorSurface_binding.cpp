#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRef.hpp"
#include "DoorSurface.hpp"

namespace ecitygml {
void add_DoorSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_DoorSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::DoorSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::DoorSurface> opaque(mod, "DoorSurface", nb::type_slots(ecitygml_DoorSurface_slots), "A door surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.");
    opaque
        .def("bounded_by", &ecitygml::DoorSurface::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::DoorSurface::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::DoorSurface::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::DoorSurface::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::DoorSurface::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::DoorSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("lod0_multi_curve", &ecitygml::DoorSurface::lod0_multi_curve, nb::rv_policy::reference_internal)
        .def("lod0_multi_surface", &ecitygml::DoorSurface::lod0_multi_surface, nb::rv_policy::reference_internal)
        .def("lod1_multi_surface", &ecitygml::DoorSurface::lod1_multi_surface, nb::rv_policy::reference_internal)
        .def("lod2_multi_surface", &ecitygml::DoorSurface::lod2_multi_surface, nb::rv_policy::reference_internal)
        .def("lod3_multi_surface", &ecitygml::DoorSurface::lod3_multi_surface, nb::rv_policy::reference_internal)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::DoorSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::DoorSurface::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::DoorSurface::relative_to_terrain)
        .def("relative_to_water", &ecitygml::DoorSurface::relative_to_water)
        .def("termination_date", &ecitygml::DoorSurface::termination_date, nb::rv_policy::reference_internal)
        .def_static("try_from", &ecitygml::DoorSurface::try_from, "feature"_a, nb::rv_policy::reference, "The feature as a door surface, or none if it is another type (Rust: `<&DoorSurface>::try_from`).")
        .def("valid_from", &ecitygml::DoorSurface::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::DoorSurface::valid_to, nb::rv_policy::reference_internal);
}

} 