#include "diplomat_nanobind_common.hpp"


#include "RelativeToWater.hpp"

namespace ecitygml {
void add_RelativeToWater_binding(nb::module_ mod) {
    nb::class_<ecitygml::RelativeToWater> e_class(mod, "RelativeToWater", "Position of a city object relative to the water surface.");
    
        nb::enum_<ecitygml::RelativeToWater::Value> enumerator(e_class, "RelativeToWater");
        enumerator
            .value("EntirelyAboveWaterSurface", ecitygml::RelativeToWater::EntirelyAboveWaterSurface)
            .value("SubstantiallyAboveWaterSurface", ecitygml::RelativeToWater::SubstantiallyAboveWaterSurface)
            .value("SubstantiallyAboveAndBelowWaterSurface", ecitygml::RelativeToWater::SubstantiallyAboveAndBelowWaterSurface)
            .value("SubstantiallyBelowWaterSurface", ecitygml::RelativeToWater::SubstantiallyBelowWaterSurface)
            .value("EntirelyBelowWaterSurface", ecitygml::RelativeToWater::EntirelyBelowWaterSurface)
            .value("TemporarilyAboveAndBelowWaterSurface", ecitygml::RelativeToWater::TemporarilyAboveAndBelowWaterSurface)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::RelativeToWater::Value>())
            .def(nb::self == ecitygml::RelativeToWater::Value())
            .def("__repr__", [](const ecitygml::RelativeToWater& self){
                return nb::str(nb::cast(ecitygml::RelativeToWater::Value(self)));
            });
}

} 