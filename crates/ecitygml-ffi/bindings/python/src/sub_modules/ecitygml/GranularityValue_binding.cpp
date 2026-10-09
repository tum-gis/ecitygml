#include "diplomat_nanobind_common.hpp"


#include "GranularityValue.hpp"

namespace ecitygml {
void add_GranularityValue_binding(nb::module_ mod) {
    nb::class_<ecitygml::GranularityValue> e_class(mod, "GranularityValue", "Level of subdivision of a transportation space (lane or way).");
    
        nb::enum_<ecitygml::GranularityValue::Value> enumerator(e_class, "GranularityValue");
        enumerator
            .value("Lane", ecitygml::GranularityValue::Lane)
            .value("Way", ecitygml::GranularityValue::Way)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::GranularityValue::Value>())
            .def(nb::self == ecitygml::GranularityValue::Value())
            .def("__repr__", [](const ecitygml::GranularityValue& self){
                return nb::str(nb::cast(ecitygml::GranularityValue::Value(self)));
            });
}

} 