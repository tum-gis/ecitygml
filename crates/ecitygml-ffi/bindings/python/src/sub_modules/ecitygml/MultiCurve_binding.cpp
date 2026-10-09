#include "diplomat_nanobind_common.hpp"


#include "AbstractGeometryKind.hpp"
#include "MultiCurve.hpp"

namespace ecitygml {
void add_MultiCurve_binding(nb::module_ mod) {
    PyType_Slot ecitygml_MultiCurve_slots[] = {
        {Py_tp_free, (void *)ecitygml::MultiCurve::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::MultiCurve> opaque(mod, "MultiCurve", nb::type_slots(ecitygml_MultiCurve_slots), "A multi curve, borrowed from a city model.");
    opaque
        .def("compute_envelope", std::move(maybe_op_unwrap(&ecitygml::MultiCurve::compute_envelope)), "Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).")
        .def("curve_member", std::move(maybe_op_unwrap(&ecitygml::MultiCurve::curve_member)), nb::keep_alive<0, 1>(), "The curve members (`gml:curveMember`).")
        .def("id", &ecitygml::MultiCurve::id, nb::rv_policy::reference_internal, "The object's `gml:id`, if it has one.")
        .def("length_3d", std::move(maybe_op_unwrap(&ecitygml::MultiCurve::length_3d)), "Sum of the members' lengths; fails with `UnresolvedReference` if a member is only an\n`xlink:href`.")
        .def("names", std::move(maybe_op_unwrap(&ecitygml::MultiCurve::names)), nb::keep_alive<0, 1>(), "The object's `gml:name`s.")
        .def_static("try_from", &ecitygml::MultiCurve::try_from, "geometry"_a, nb::rv_policy::reference, "The geometry as a `MultiCurve`, or none if it is another type (Rust: nested\n`AbstractGeometryKind` variants).");
}

} 