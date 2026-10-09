#include "diplomat_nanobind_common.hpp"


#include "SpaceType.hpp"

namespace ecitygml {
void add_SpaceType_binding(nb::module_ mod) {
    nb::class_<ecitygml::SpaceType> e_class(mod, "SpaceType", "Whether a space is closed, open or semi-open.");
    
        nb::enum_<ecitygml::SpaceType::Value> enumerator(e_class, "SpaceType");
        enumerator
            .value("Closed", ecitygml::SpaceType::Closed)
            .value("Open", ecitygml::SpaceType::Open)
            .value("SemiOpen", ecitygml::SpaceType::SemiOpen)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::SpaceType::Value>())
            .def(nb::self == ecitygml::SpaceType::Value())
            .def("__repr__", [](const ecitygml::SpaceType& self){
                return nb::str(nb::cast(ecitygml::SpaceType::Value(self)));
            });
}

} 