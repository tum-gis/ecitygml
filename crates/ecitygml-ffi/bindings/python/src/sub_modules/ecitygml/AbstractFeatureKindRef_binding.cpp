#include "diplomat_nanobind_common.hpp"


#include "AbstractCityObjectKindRef.hpp"
#include "AbstractFeatureKindRef.hpp"
#include "AbstractSpaceBoundaryKind.hpp"

namespace ecitygml {
void add_AbstractFeatureKindRef_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractFeatureKindRef_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractFeatureKindRef::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractFeatureKindRef> opaque(mod, "AbstractFeatureKindRef", nb::type_slots(ecitygml_AbstractFeatureKindRef_slots), "A reference to a feature of any type; convert it with e.g. `TrafficSpace::try_from`.");
    opaque
        .def("feature_type", &ecitygml::AbstractFeatureKindRef::feature_type)
        .def_static("from_city_object", std::move(maybe_op_unwrap(&ecitygml::AbstractFeatureKindRef::from_city_object)), "city_object"_a, nb::keep_alive<0, 1>(), "The feature a city object is, to convert it with e.g. `Building::try_from` (Rust wraps it in\nthe `AbstractFeatureWithLifespanKind(AbstractCityObjectKind(_))` variants; it has no `From`).")
        .def_static("from_space_boundary", std::move(maybe_op_unwrap(&ecitygml::AbstractFeatureKindRef::from_space_boundary)), "boundary"_a, nb::keep_alive<0, 1>(), "The feature a space boundary is (Rust: `From<&AbstractSpaceBoundaryKind>`), to convert it\nwith e.g. `WallSurface::try_from`.");
}

} 