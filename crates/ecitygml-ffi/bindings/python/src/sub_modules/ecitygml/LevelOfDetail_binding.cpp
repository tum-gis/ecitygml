#include "diplomat_nanobind_common.hpp"


#include "LevelOfDetail.hpp"

namespace ecitygml {
void add_LevelOfDetail_binding(nb::module_ mod) {
    nb::class_<ecitygml::LevelOfDetail> e_class(mod, "LevelOfDetail", "A CityGML level of detail (LoD 0 to 3).");
    
        nb::enum_<ecitygml::LevelOfDetail::Value> enumerator(e_class, "LevelOfDetail");
        enumerator
            .value("Zero", ecitygml::LevelOfDetail::Zero)
            .value("One", ecitygml::LevelOfDetail::One)
            .value("Two", ecitygml::LevelOfDetail::Two)
            .value("Three", ecitygml::LevelOfDetail::Three)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::LevelOfDetail::Value>())
            .def(nb::self == ecitygml::LevelOfDetail::Value())
            .def("__repr__", [](const ecitygml::LevelOfDetail& self){
                return nb::str(nb::cast(ecitygml::LevelOfDetail::Value(self)));
            });
}

} 