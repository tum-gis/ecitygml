#include "diplomat_nanobind_common.hpp"


#include "Triangulation.hpp"

namespace ecitygml {
void add_Triangulation_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Triangulation_slots[] = {
        {Py_tp_free, (void *)ecitygml::Triangulation::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Triangulation> opaque(mod, "Triangulation", nb::type_slots(ecitygml_Triangulation_slots), "A triangulated surface and the members that couldn't be triangulated.");
    opaque
        .def("has_skipped", &ecitygml::Triangulation::has_skipped, "Whether some members couldn't be triangulated.")
        .def("skipped", std::move(maybe_op_unwrap(&ecitygml::Triangulation::skipped)), nb::keep_alive<0, 1>(), "Why members couldn't be triangulated, one error each.")
        .def("surface", &ecitygml::Triangulation::surface, nb::rv_policy::reference_internal);
}

} 