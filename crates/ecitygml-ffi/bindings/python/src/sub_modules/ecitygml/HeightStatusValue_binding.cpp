#include "diplomat_nanobind_common.hpp"


#include "HeightStatusValue.hpp"

namespace ecitygml {
void add_HeightStatusValue_binding(nb::module_ mod) {
    nb::class_<ecitygml::HeightStatusValue> e_class(mod, "HeightStatusValue", "Whether a height was estimated or measured.");
    
        nb::enum_<ecitygml::HeightStatusValue::Value> enumerator(e_class, "HeightStatusValue");
        enumerator
            .value("Estimated", ecitygml::HeightStatusValue::Estimated)
            .value("Measured", ecitygml::HeightStatusValue::Measured)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::HeightStatusValue::Value>())
            .def(nb::self == ecitygml::HeightStatusValue::Value())
            .def("__repr__", [](const ecitygml::HeightStatusValue& self){
                return nb::str(nb::cast(ecitygml::HeightStatusValue::Value(self)));
            });
}

} 