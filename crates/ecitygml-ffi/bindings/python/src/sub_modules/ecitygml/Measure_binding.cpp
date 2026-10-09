#include "diplomat_nanobind_common.hpp"


#include "Measure.hpp"

namespace ecitygml {
void add_Measure_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Measure_slots[] = {
        {Py_tp_free, (void *)ecitygml::Measure::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Measure> opaque(mod, "Measure", nb::type_slots(ecitygml_Measure_slots), "A numeric value with its unit of measure, borrowed from a city model.");
    opaque
        .def("uom", &ecitygml::Measure::uom, "Unit of measure (`uom`), e.g. `m2`.")
        .def("value", &ecitygml::Measure::value);
}

} 