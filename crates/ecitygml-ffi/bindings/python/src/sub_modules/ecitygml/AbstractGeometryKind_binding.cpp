#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"

namespace ecitygml {
void add_AbstractGeometryKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractGeometryKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractGeometryKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractGeometryKind> opaque(mod, "AbstractGeometryKind", nb::type_slots(ecitygml_AbstractGeometryKind_slots), "A geometry of any type, borrowed from a city model; convert it with `MultiSurface::try_from`,\n`MultiCurve::try_from`, `Point::try_from`, `Solid::try_from`, `AbstractSurfaceKind::try_from`\nor `AbstractCurveKind::try_from`. Not bound yet: `MultiPoint`, `MultiGeometry`.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::AbstractGeometryKind::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("geometry_type", &ecitygml::AbstractGeometryKind::geometry_type)
        .def("id", &ecitygml::AbstractGeometryKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractGeometryKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::AbstractGeometryKind::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.");
}

} 