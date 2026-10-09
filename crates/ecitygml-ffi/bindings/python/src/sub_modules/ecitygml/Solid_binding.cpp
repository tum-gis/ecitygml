#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"
#include "Solid.hpp"

namespace ecitygml {
void add_Solid_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Solid_slots[] = {
        {Py_tp_free, (void *)ecitygml::Solid::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Solid> opaque(mod, "Solid", nb::type_slots(ecitygml_Solid_slots), "A solid, borrowed from a city model.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::Solid::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("exterior", &ecitygml::Solid::exterior, nb::rv_policy::reference_internal)
        .def("id", &ecitygml::Solid::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("interior", std::move(maybe_op_unwrap(&ecitygml::Solid::interior)), nb::keep_alive<0, 1>())
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Solid::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::Solid::points)), nb::keep_alive<0, 1>(), "All positions of the exterior shell.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::Solid::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::Solid::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as a `Solid`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).")
        .def("volume_3d", std::move(maybe_op_unwrap(&ecitygml::Solid::volume_3d)), "Volume of the exterior shell. Stricter than Rust, which skips shell members it can't\ntriangulate (and panics on some): fails with `UnresolvedReference` if a member is only an\n`xlink:href`, and with `InvalidArgument` if a member can't be triangulated, so the volume is\nnever computed from an incomplete shell.");
}

} 