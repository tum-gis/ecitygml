#include "diplomat_nanobind_common.hpp"


#include "TrafficDirectionValue.hpp"

namespace ecitygml {
void add_TrafficDirectionValue_binding(nb::module_ mod) {
    nb::class_<ecitygml::TrafficDirectionValue> e_class(mod, "TrafficDirectionValue", "Allowed traffic direction of a traffic space.");
    
        nb::enum_<ecitygml::TrafficDirectionValue::Value> enumerator(e_class, "TrafficDirectionValue");
        enumerator
            .value("Forwards", ecitygml::TrafficDirectionValue::Forwards)
            .value("Backwards", ecitygml::TrafficDirectionValue::Backwards)
            .value("Both", ecitygml::TrafficDirectionValue::Both)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::TrafficDirectionValue::Value>())
            .def(nb::self == ecitygml::TrafficDirectionValue::Value())
            .def("__repr__", [](const ecitygml::TrafficDirectionValue& self){
                return nb::str(nb::cast(ecitygml::TrafficDirectionValue::Value(self)));
            });
}

} 