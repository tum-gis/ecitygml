#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfacePatchKind.hpp"
#include "Triangle.hpp"

namespace ecitygml {
void add_Triangle_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Triangle_slots[] = {
        {Py_tp_free, (void *)ecitygml::Triangle::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Triangle> opaque(mod, "Triangle", nb::type_slots(ecitygml_Triangle_slots), "A triangle, borrowed from a city model.");
    opaque
        .def("a", &ecitygml::Triangle::a, nb::rv_policy::reference_internal)
        .def("area", &ecitygml::Triangle::area)
        .def("b", &ecitygml::Triangle::b, nb::rv_policy::reference_internal)
        .def("c", &ecitygml::Triangle::c, nb::rv_policy::reference_internal)
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::Triangle::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("exterior", &ecitygml::Triangle::exterior, nb::rv_policy::reference_internal)
        .def("points", std::move(maybe_op_unwrap(&ecitygml::Triangle::points)), nb::keep_alive<0, 1>(), "The three corners.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::Triangle::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::Triangle::try_from, "patch"_a, nb::rv_policy::reference, "The patch as a triangle, or none if it is another type (Rust: `Triangle::try_from`, which\ntakes the patch by value).");
}

} 