#include "diplomat_nanobind_common.hpp"


#include "AbstractCurveKind.hpp"
#include "LineString.hpp"

namespace ecitygml {
void add_LineString_binding(nb::module_ mod) {
    PyType_Slot ecitygml_LineString_slots[] = {
        {Py_tp_free, (void *)ecitygml::LineString::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::LineString> opaque(mod, "LineString", nb::type_slots(ecitygml_LineString_slots), "A line string, borrowed from a city model.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::LineString::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::LineString::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("length_3d", &ecitygml::LineString::length_3d)
        .def("names", std::move(maybe_op_unwrap(&ecitygml::LineString::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::LineString::points)), nb::keep_alive<0, 1>(), "The positions (`gml:posList`).")
        .def_static("try_from", &ecitygml::LineString::try_from, "curve"_a, nb::rv_policy::reference, "The curve as a line string, or none if it is another type (Rust: `LineString::try_from`,\nwhich takes the curve by value).");
}

} 