#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfacePatchKind.hpp"

namespace ecitygml {
void add_AbstractSurfacePatchKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSurfacePatchKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSurfacePatchKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSurfacePatchKind> opaque(mod, "AbstractSurfacePatchKind", nb::type_slots(ecitygml_AbstractSurfacePatchKind_slots), "A surface patch of any type, borrowed from a city model; convert it with\n`PolygonPatch::try_from` or `Triangle::try_from`. Patches aren't GML objects (no `gml:id`).");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfacePatchKind::area_3d)))
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfacePatchKind::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfacePatchKind::points)), nb::keep_alive<0, 1>(), "The patch's positions.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::AbstractSurfacePatchKind::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.");
}

} 