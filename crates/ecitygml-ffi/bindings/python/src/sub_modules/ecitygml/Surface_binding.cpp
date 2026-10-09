#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfaceKind.hpp"
#include "Surface.hpp"

namespace ecitygml {
void add_Surface_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Surface_slots[] = {
        {Py_tp_free, (void *)ecitygml::Surface::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Surface> opaque(mod, "Surface", nb::type_slots(ecitygml_Surface_slots), "A surface made of patches, borrowed from a city model.");
    opaque
        .def("area_3d", std::move(maybe_op_unwrap(&ecitygml::Surface::area_3d)))
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::Surface::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("id", &ecitygml::Surface::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::Surface::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("patches", std::move(maybe_op_unwrap(&ecitygml::Surface::patches)), nb::keep_alive<0, 1>(), "The patches (`gml:patches`).")
        .def("points", std::move(maybe_op_unwrap(&ecitygml::Surface::points)), nb::keep_alive<0, 1>(), "All positions of the patches.")
        .def("triangulate", std::move(maybe_op_unwrap(&ecitygml::Surface::triangulate)), "Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to\ntriangulate are listed in `Triangulation::skipped`; as in egml, members that are only an\n`xlink:href` are left out without such an entry.")
        .def_static("try_from", &ecitygml::Surface::try_from, "surface"_a, nb::rv_policy::reference, "The surface as a `gml:Surface`, or none if it is another type (Rust: `Surface::try_from`,\nwhich takes the surface by value).");
}

} 