#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfaceKind.hpp"
#include "Shell.hpp"

namespace ecitygml {
void add_Shell_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Shell_slots[] = {
        {Py_tp_free, (void *)ecitygml::Shell::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Shell> opaque(mod, "Shell", nb::type_slots(ecitygml_Shell_slots), "A shell (closed surface), borrowed from a city model.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::Shell::area_3d)))
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::Shell::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::Shell::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("members", std::move(maybe_op_unwrap(&ecitygml::Shell::members)), nb::keep_alive<0, 1>(), "The surface members (`gml:surfaceMember`).")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Shell::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::Shell::points)), nb::keep_alive<0, 1>(), "All positions of the inline members.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::Shell::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::Shell::try_from, "surface"_a, nb::rv_policy::reference, "The surface as a shell, or none if it is another type (Rust: `Shell::try_from`, which\ntakes the surface by value).")
        .def("volume_3d", std::move(maybe_op_unwrap(&ecitygml::Shell::volume_3d)), "Enclosed volume; fails with `UnresolvedReference` if a member is only an `xlink:href`.");
}

} 