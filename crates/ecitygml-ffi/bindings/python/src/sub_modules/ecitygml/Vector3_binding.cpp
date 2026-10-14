#include "diplomat_nanobind_common.hpp"


#include "Vector3.hpp"

namespace ecitygml {
void add_Vector3_binding(nb::module_ mod) {
    nb::class_<ecitygml::Vector3> st(mod, "Vector3", "A 3D vector, passed by value (e.g. the translation of `CityModel::apply_translation`).");
    st
        .def(nb::init<>())
        .def(nb::init<double, double, double>(), "x"_a.none(),  "y"_a.none(),  "z"_a.none())
        .def_rw("x", &ecitygml::Vector3::x)
        .def_rw("y", &ecitygml::Vector3::y)
        .def_rw("z", &ecitygml::Vector3::z);
}

} 