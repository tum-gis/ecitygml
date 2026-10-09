#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"
#include "Point.hpp"

namespace ecitygml {
void add_Point_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Point_slots[] = {
        {Py_tp_free, (void *)ecitygml::Point::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Point> opaque(mod, "Point", nb::type_slots(ecitygml_Point_slots), "A point, borrowed from a city model.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::Point::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::Point::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Point::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("pos", &ecitygml::Point::pos, nb::rv_policy::reference_internal, "The position (`gml:pos`).")
        .def_static("try_from", &ecitygml::Point::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as a `Point`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).");
}

} 