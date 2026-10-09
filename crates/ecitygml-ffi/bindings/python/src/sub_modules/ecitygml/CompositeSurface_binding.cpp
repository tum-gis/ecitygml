#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfaceKind.hpp"
#include "CompositeSurface.hpp"

namespace ecitygml {
void add_CompositeSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CompositeSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::CompositeSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CompositeSurface> opaque(mod, "CompositeSurface", nb::type_slots(ecitygml_CompositeSurface_slots), "A composite surface, borrowed from a city model.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::area_3d)), "Sum of the members' areas; fails with `UnresolvedReference` if a member is only an\n`xlink:href`.")
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::CompositeSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::points)), nb::keep_alive<0, 1>(), "All positions of the inline members.")
        .def("surface_member", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::surface_member)), nb::keep_alive<0, 1>(), "The surface members (`gml:surfaceMember`).")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::CompositeSurface::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::CompositeSurface::try_from, "surface"_a, nb::rv_policy::reference, "The surface as a composite surface, or none if it is another type (Rust:\n`CompositeSurface::try_from`, which takes the surface by value).");
}

} 