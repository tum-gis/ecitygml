#include "diplomat_nanobind_common.hpp"


#include "ExternalReference.hpp"

namespace ecitygml {
void add_ExternalReference_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ExternalReference_slots[] = {
        {Py_tp_free, (void *)ecitygml::ExternalReference::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ExternalReference> opaque(mod, "ExternalReference", nb::type_slots(ecitygml_ExternalReference_slots), "A reference to an object in another information system, borrowed from a city model.");
    opaque
        .def("information_system", &ecitygml::ExternalReference::information_system)
        .def("relation_type", &ecitygml::ExternalReference::relation_type)
        .def("target_resource", &ecitygml::ExternalReference::target_resource);
}

} 