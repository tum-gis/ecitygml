#include "diplomat_nanobind_common.hpp"


#include "AbstractCurveKind.hpp"
#include "AbstractGeometryKind.hpp"

namespace ecitygml {
void add_AbstractCurveKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCurveKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCurveKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCurveKind> opaque(mod, "AbstractCurveKind", nb::type_slots(ecitygml_AbstractCurveKind_slots), "A curve of any type, borrowed from a city model; convert it with e.g. `LineString::try_from`.\nRings: `AbstractRingKind::try_from`.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::AbstractCurveKind::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("geometry_type", &ecitygml::AbstractCurveKind::geometry_type)
        .def("id", &ecitygml::AbstractCurveKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("length_3d", &ecitygml::AbstractCurveKind::length_3d)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractCurveKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def_static("try_from", &ecitygml::AbstractCurveKind::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as an `AbstractCurveKind`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).");
}

} 