#include "diplomat_nanobind_common.hpp"


#include "TransformationMatrix4x4.hpp"

namespace ecitygml {
void add_TransformationMatrix4x4_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TransformationMatrix4x4_slots[] = {
        {Py_tp_free, (void *)ecitygml::TransformationMatrix4x4::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TransformationMatrix4x4> opaque(mod, "TransformationMatrix4x4", nb::type_slots(ecitygml_TransformationMatrix4x4_slots), "A 4x4 transformation matrix, borrowed from a city model.");
    opaque
        .def("get", std::move(maybe_op_unwrap(&ecitygml::TransformationMatrix4x4::get)), "row"_a, "column"_a, "The entry at `row` and `column` (0 to 3), as nalgebra's `matrix()[(row, column)]`; fails\nwith `InvalidArgument` instead of panicking above 3. Rust's `to_row_major()` returns a\n`Vec`, which the Python backend can only return through NumPy.");
}

} 