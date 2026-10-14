#include "diplomat_nanobind_common.hpp"


#include "AbstractCityObjectKind.hpp"
#include "AbstractCityObjectKindRef.hpp"

namespace ecitygml {
void add_AbstractCityObjectKindRef_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCityObjectKindRef_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCityObjectKindRef::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCityObjectKindRef> opaque(mod, "AbstractCityObjectKindRef", nb::type_slots(ecitygml_AbstractCityObjectKindRef_slots), "A reference to a city object of any type; convert it with\n`AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.");
    opaque
        .def("feature_type", &ecitygml::AbstractCityObjectKindRef::feature_type)
        .def_static("from_city_object", std::move(maybe_op_unwrap(&ecitygml::AbstractCityObjectKindRef::from_city_object)), "city_object"_a, nb::keep_alive<0, 1>(), "A reference to a city object (Rust: `From<&AbstractCityObjectKind>`), to convert it with\n`AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.");
}

} 