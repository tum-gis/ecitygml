#include "diplomat_nanobind_common.hpp"


#include "AbstractCityObjectKind.hpp"

namespace ecitygml {
void add_AbstractCityObjectKind_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCityObjectKind_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCityObjectKind::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCityObjectKind> opaque(mod, "AbstractCityObjectKind", nb::type_slots(ecitygml_AbstractCityObjectKind_slots), "A city object of any type (e.g. a building or road), borrowed from a city model. It has the\ngetters of every ancestor; for the concrete type, convert it with\n`AbstractCityObjectKindRef::from_city_object`, `AbstractFeatureKindRef::from_city_object` and\ne.g. `Building::try_from`.");
    opaque
        .def("bounded_by", &ecitygml::AbstractCityObjectKind::bounded_by, nb::rv_policy::reference_internal, "The feature's bounding shape (`gml:boundedBy`), if it has one.")
        .def("creation_date", &ecitygml::AbstractCityObjectKind::creation_date, nb::rv_policy::reference_internal)
        .def("external_references", std::move(maybe_op_unwrap(&ecitygml::AbstractCityObjectKind::external_references)), nb::keep_alive<0, 1>())
        .def("feature_id", &ecitygml::AbstractCityObjectKind::feature_id, nb::rv_policy::reference_internal, "The feature's `gml:id`.")
        .def("feature_type", &ecitygml::AbstractCityObjectKind::feature_type)
        .def("generic_attributes", std::move(maybe_op_unwrap(&ecitygml::AbstractCityObjectKind::generic_attributes)), nb::keep_alive<0, 1>())
        .def("id", &ecitygml::AbstractCityObjectKind::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::AbstractCityObjectKind::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def("related_to", std::move(maybe_op_unwrap(&ecitygml::AbstractCityObjectKind::related_to)), nb::keep_alive<0, 1>(), "Relations to other city objects (`relatedTo`).")
        .def("relative_to_terrain", &ecitygml::AbstractCityObjectKind::relative_to_terrain)
        .def("relative_to_water", &ecitygml::AbstractCityObjectKind::relative_to_water)
        .def("termination_date", &ecitygml::AbstractCityObjectKind::termination_date, nb::rv_policy::reference_internal)
        .def("valid_from", &ecitygml::AbstractCityObjectKind::valid_from, nb::rv_policy::reference_internal)
        .def("valid_to", &ecitygml::AbstractCityObjectKind::valid_to, nb::rv_policy::reference_internal);
}

} 