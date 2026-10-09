#include "diplomat_nanobind_common.hpp"


#include "GenericAttributeKind.hpp"
#include "MeasureAttribute.hpp"

namespace ecitygml {
void add_MeasureAttribute_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MeasureAttribute_slots[] = {
        {Py_tp_free, (void *)ecitygml::MeasureAttribute::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MeasureAttribute> opaque(mod, "MeasureAttribute", nb::type_slots(ecitygml_MeasureAttribute_slots), "A generic attribute with a value and unit of measure, borrowed from a city model.");
    opaque
        .def("name", &ecitygml::MeasureAttribute::name)
        .def_static("try_from", &ecitygml::MeasureAttribute::try_from, "attribute"_a, nb::rv_policy::reference, "The attribute as a measure attribute, or none if it is another kind (Rust has no\n`as_measure`; it matches `GenericAttributeKind::MeasureAttribute`).")
        .def("value", &ecitygml::MeasureAttribute::value, nb::rv_policy::reference_internal);
}

} 