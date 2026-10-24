#include "diplomat_nanobind_common.hpp"


#include "Reference.hpp"
#include "TrafficSpaceReference.hpp"

namespace ecitygml {
void add_Reference_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Reference_slots[] = {
        {Py_tp_free, (void *)ecitygml::Reference::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Reference> opaque(mod, "Reference", nb::type_slots(ecitygml_Reference_slots), "A reference to an object by `xlink:href`, borrowed from a city model.");
    opaque
        .def_static("from_traffic_space_reference", std::move(maybe_op_unwrap(&ecitygml::Reference::from_traffic_space_reference)), "reference"_a, "An owned copy of a traffic space reference (Rust: `From<&TrafficSpaceReference>`).")
        .def("href", &ecitygml::Reference::href, nb::rv_policy::reference_internal);
}

} 