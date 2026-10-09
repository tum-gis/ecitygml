#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfaceKind.hpp"
#include "TriangulatedSurface.hpp"

namespace ecitygml {
void add_TriangulatedSurface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TriangulatedSurface_slots[] = {
        {Py_tp_free, (void *)ecitygml::TriangulatedSurface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TriangulatedSurface> opaque(mod, "TriangulatedSurface", nb::type_slots(ecitygml_TriangulatedSurface_slots), "A surface made of triangles, borrowed from a city model or a triangulation.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::TriangulatedSurface::area_3d)))
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::TriangulatedSurface::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::TriangulatedSurface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::TriangulatedSurface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::TriangulatedSurface::points)), nb::keep_alive<0, 1>(), "All corners of the triangles.")
        .def("surface", &ecitygml::TriangulatedSurface::surface, nb::rv_policy::reference_internal, "The underlying surface, whose patches are the triangles.")
        .def("triangles", std::move(maybe_op_unwrap(&ecitygml::TriangulatedSurface::triangles)), nb::keep_alive<0, 1>())
        .def_static("try_from", &ecitygml::TriangulatedSurface::try_from, "surface"_a, nb::rv_policy::reference, "The surface as a triangulated surface, or none if it is another type (Rust: a\n`TriangulatedSurface` in `AbstractSurfaceKind::SurfaceKind`).");
}

} 