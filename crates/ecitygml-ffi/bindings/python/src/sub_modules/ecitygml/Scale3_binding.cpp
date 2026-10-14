#include "diplomat_nanobind_common.hpp"


#include "Scale3.hpp"

namespace ecitygml {
void add_Scale3_binding(nb::module_ mod) {
    nb::class_<ecitygml::Scale3> st(mod, "Scale3", "A scale factor per axis, passed by value (the argument of `CityModel::apply_scale`).");
    st
        .def(nb::init<>())
        .def(nb::init<double, double, double>(), "x"_a.none(),  "y"_a.none(),  "z"_a.none())
        .def_rw("x", &ecitygml::Scale3::x)
        .def_rw("y", &ecitygml::Scale3::y)
        .def_rw("z", &ecitygml::Scale3::z);
}

} 