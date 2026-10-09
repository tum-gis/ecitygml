#include "diplomat_nanobind_common.hpp"


#include "CityModel.hpp"

namespace ecitygml {
void add_CityModel_binding(nb::module_ mod) {
    PyType_Slot ecitygml_CityModel_slots[] = {
        {Py_tp_free, (void *)ecitygml::CityModel::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::CityModel> opaque(mod, "CityModel", nb::type_slots(ecitygml_CityModel_slots), "A city model; mutable for `recompute_child_bounding_shapes`.");
    opaque
        .def("bounded_by", &ecitygml::CityModel::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("city_objects_len", &ecitygml::CityModel::city_objects_len, "Number of direct `cityObjectMember`s.")
        .def("creation_date", &ecitygml::CityModel::creation_date, nb::rv_policy::reference_internal)
        .def("feature_id", &ecitygml::CityModel::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("id", &ecitygml::CityModel::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("iter_city_objects", std::move(maybe_op_unwrap(&ecitygml::CityModel::iter_city_objects)), nb::keep_alive<0, 1>(), "Lazily iterates over all city objects at any depth, without the city model itself (Rust:\n`iter_city_objects`).")
        .def("iter_features", std::move(maybe_op_unwrap(&ecitygml::CityModel::iter_features)), nb::keep_alive<0, 1>(), "Lazily iterates over all features at any depth (Rust: `IterFeatures::iter_features`).")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::CityModel::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("recompute_child_bounding_shapes", &ecitygml::CityModel::recompute_child_bounding_shapes, "Recomputes the bounding shape of every feature below the city model from its geometry.")
        .def("termination_date", &ecitygml::CityModel::termination_date, nb::rv_policy::reference_internal)
        .def("valid_from", &ecitygml::CityModel::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::CityModel::valid_to, nb::rv_policy::reference_internal);
}

} 