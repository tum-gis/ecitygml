#include "diplomat_nanobind_common.hpp"


#include "AbstractCurveKind.hpp"
#include "AbstractRingKind.hpp"

namespace ecitygml {
void add_AbstractRingKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractRingKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractRingKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractRingKind> opaque(mod, "AbstractRingKind", nb::type_slots(ecitygml_AbstractRingKind_slots), "A ring of any type, borrowed from a city model; convert it with `LinearRing::try_from`.");
    opaque
        .def("area_3d", &ecitygml::AbstractRingKind::area_3d)
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::AbstractRingKind::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("geometry_type", &ecitygml::AbstractRingKind::geometry_type)
        .def("id", &ecitygml::AbstractRingKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("length_3d", &ecitygml::AbstractRingKind::length_3d)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractRingKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::AbstractRingKind::points)), nb::keep_alive<0, 1>(), "The positions, without the repeated closing position.")
        .def_static("try_from", &ecitygml::AbstractRingKind::try_from, "curve"_a, nb::rv_policy::reference, "The curve as a ring, or none if it is another type (Rust: `AbstractRingKind::try_from`,\nwhich takes the curve by value).");
}

} 