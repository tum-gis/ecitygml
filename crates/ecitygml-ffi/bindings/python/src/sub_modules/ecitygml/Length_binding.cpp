#include "diplomat_nanobind_common.hpp"


#include "Length.hpp"

namespace ecitygml {
void add_Length_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Length_slots[] = {
        {Py_tp_free, (void *)ecitygml::Length::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Length> opaque(mod, "Length", nb::type_slots(ecitygml_Length_slots), "A length with its unit of measure, borrowed from a city model.");
    opaque
        .def("uom", &ecitygml::Length::uom, "Unit of measure (`uom`), e.g. `m`.")
        .def("value", &ecitygml::Length::value);
}

} 