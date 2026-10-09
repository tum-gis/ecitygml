#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"
#include "MultiSurface.hpp"

namespace ecitygml {
void add_MultiSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MultiSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::MultiSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MultiSurface> opaque(mod, "MultiSurface", nb::type_slots(ecitygml_MultiSurface_slots), "A multi surface, borrowed from a city model.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::area_3d)), "Sum of the members' areas; fails with `UnresolvedReference` if a member is only an\n`xlink:href`.")
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::MultiSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::points)), nb::keep_alive<0, 1>(), "All positions of the inline members.")
        .def("surface_member", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::surface_member)), nb::keep_alive<0, 1>(), "The surface members (`gml:surfaceMember`).")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::MultiSurface::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::MultiSurface::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as a `MultiSurface`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).");
}

} 