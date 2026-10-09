#include "diplomat_nanobind_common.hpp"


#include "AbstractRingKind.hpp"
#include "LinearRing.hpp"

namespace ecitygml {
void add_LinearRing_binding(nb::module_ mod) {
    PyType_Slot ecitygml_LinearRing_slots[] = {
        {Py_tp_free, (void *)ecitygml::LinearRing::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::LinearRing> opaque(mod, "LinearRing", nb::type_slots(ecitygml_LinearRing_slots), "A linear ring, borrowed from a city model.");
    opaque
        .def("area_3d", &ecitygml::LinearRing::area_3d)
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::LinearRing::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::LinearRing::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("length_3d", &ecitygml::LinearRing::length_3d)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::LinearRing::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::LinearRing::points)), nb::keep_alive<0, 1>(), "The positions, without the repeated closing position.")
        .def_static("try_from", &ecitygml::LinearRing::try_from, "ring"_a, nb::rv_policy::reference, "The ring as a linear ring, or none if it is another type (Rust: `LinearRing::try_from`,\nwhich takes the ring by value). Follows nested rings (`AbstractRingKind::AbstractRingKind`).");
}

} 