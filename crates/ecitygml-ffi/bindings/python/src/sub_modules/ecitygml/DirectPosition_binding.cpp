#include "diplomat_nanobind_common.hpp"


#include "DirectPosition.hpp"

namespace ecitygml {
void add_DirectPosition_binding(nb::module_ mod) {
    PyType_Slot ecitygml_DirectPosition_slots[] = {
        {Py_tp_free, (void *)ecitygml::DirectPosition::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::DirectPosition> opaque(mod, "DirectPosition", nb::type_slots(ecitygml_DirectPosition_slots), "A 3D coordinate, created or borrowed from a city model.");
    opaque
        .def(nb::new_(std::move(maybe_op_unwrap(&ecitygml::DirectPosition::new_))), "x"_a, "y"_a, "z"_a, "Creates a position; fails with `InvalidArgument` if a coordinate is NaN or infinite.")
        .def("x", &ecitygml::DirectPosition::x)
        .def("y", &ecitygml::DirectPosition::y)
        .def("z", &ecitygml::DirectPosition::z);
}

} 