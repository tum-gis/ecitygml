#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfacePatchKind.hpp"
#include "PolygonPatch.hpp"

namespace ecitygml {
void add_PolygonPatch_binding(nb::module_ mod) {
    PyType_Slot ecitygml_PolygonPatch_slots[] = {
        {Py_tp_free, (void *)ecitygml::PolygonPatch::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::PolygonPatch> opaque(mod, "PolygonPatch", nb::type_slots(ecitygml_PolygonPatch_slots), "A polygon patch, borrowed from a city model.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::PolygonPatch::area_3d)), "Exterior area minus the holes; fails if the patch has no exterior ring.")
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::PolygonPatch::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("exterior", &ecitygml::PolygonPatch::exterior, nb::rv_policy::reference_internal)
        .def("interior", std::move(maybe_op_unwrap(&ecitygml::PolygonPatch::interior)), nb::keep_alive<0, 1>())
        .def("points", std::move(maybe_op_unwrap(&ecitygml::PolygonPatch::points)), nb::keep_alive<0, 1>(), "All positions of the exterior and interior rings.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::PolygonPatch::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::PolygonPatch::try_from, "patch"_a, nb::rv_policy::reference, "The patch as a polygon patch, or none if it is another type (Rust: `PolygonPatch::try_from`, which\ntakes the patch by value).");
}

} 