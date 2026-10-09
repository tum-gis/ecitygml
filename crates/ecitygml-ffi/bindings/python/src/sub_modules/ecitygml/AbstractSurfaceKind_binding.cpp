#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"
#include "AbstractSurfaceKind.hpp"

namespace ecitygml {
void add_AbstractSurfaceKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSurfaceKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSurfaceKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSurfaceKind> opaque(mod, "AbstractSurfaceKind", nb::type_slots(ecitygml_AbstractSurfaceKind_slots), "A surface of any type, borrowed from a city model; convert it with `Polygon::try_from`,\n`CompositeSurface::try_from`, `Shell::try_from`, `Surface::try_from` or\n`TriangulatedSurface::try_from`.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfaceKind::area_3d)))
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfaceKind::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("geometry_type", &ecitygml::AbstractSurfaceKind::geometry_type)
        .def("id", &ecitygml::AbstractSurfaceKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfaceKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfaceKind::points)), nb::keep_alive<0, 1>())
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfaceKind::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::AbstractSurfaceKind::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as an `AbstractSurfaceKind`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).");
}

} 