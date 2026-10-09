#include "diplomat_nanobind_common.hpp"


#include "ImplicitGeometry.hpp"

namespace ecitygml {
void add_ImplicitGeometry_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ImplicitGeometry_slots[] = {
        {Py_tp_free, (void *)ecitygml::ImplicitGeometry::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ImplicitGeometry> opaque(mod, "ImplicitGeometry", nb::type_slots(ecitygml_ImplicitGeometry_slots), "A prototype geometry placed by a transformation and a reference point, borrowed from a city\nmodel. Not bound yet: appearances.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::ImplicitGeometry::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("library_object", &ecitygml::ImplicitGeometry::library_object, "Reference to the prototype in an external library.")
        .def("mime_type", &ecitygml::ImplicitGeometry::mime_type, nb::rv_policy::reference_internal)
        .def("object_id", &ecitygml::ImplicitGeometry::object_id, nb::rv_policy::reference_internal, "Identifies the implicit geometry (from its `gml:id`).")
        .def("reference_point", &ecitygml::ImplicitGeometry::reference_point, nb::rv_policy::reference_internal)
        .def("relative_geometry", &ecitygml::ImplicitGeometry::relative_geometry, nb::rv_policy::reference_internal, "The prototype geometry, in its own coordinate system.")
        .def("transformation_matrix", &ecitygml::ImplicitGeometry::transformation_matrix, nb::rv_policy::reference_internal);
}

} 