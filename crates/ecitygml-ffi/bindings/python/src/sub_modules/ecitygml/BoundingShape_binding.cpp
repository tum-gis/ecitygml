#include "diplomat_nanobind_common.hpp"


#include "BoundingShape.hpp"

namespace ecitygml {
void add_BoundingShape_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BoundingShape_slots[] = {
        {Py_tp_free, (void *)ecitygml::BoundingShape::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BoundingShape> opaque(mod, "BoundingShape", nb::type_slots(ecitygml_BoundingShape_slots), "The bounding shape of a feature (`gml:boundedBy`), borrowed from a city model.");
    opaque
        .def("envelope", &ecitygml::BoundingShape::envelope, nb::rv_policy::reference_internal, "The envelope; none if the shape is nil.");
}

} 