#include "diplomat_nanobind_common.hpp"


#include "RelativeToTerrain.hpp"

namespace ecitygml {
void add_RelativeToTerrain_binding(nb::module_ mod) {
    nb::class_<ecitygml::RelativeToTerrain> e_class(mod, "RelativeToTerrain", "Position of a city object relative to the terrain.");
    
        nb::enum_<ecitygml::RelativeToTerrain::Value> enumerator(e_class, "RelativeToTerrain");
        enumerator
            .value("EntirelyAboveTerrain", ecitygml::RelativeToTerrain::EntirelyAboveTerrain)
            .value("SubstantiallyAboveTerrain", ecitygml::RelativeToTerrain::SubstantiallyAboveTerrain)
            .value("SubstantiallyAboveAndBelowTerrain", ecitygml::RelativeToTerrain::SubstantiallyAboveAndBelowTerrain)
            .value("SubstantiallyBelowTerrain", ecitygml::RelativeToTerrain::SubstantiallyBelowTerrain)
            .value("EntirelyBelowTerrain", ecitygml::RelativeToTerrain::EntirelyBelowTerrain)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::RelativeToTerrain::Value>())
            .def(nb::self == ecitygml::RelativeToTerrain::Value())
            .def("__repr__", [](const ecitygml::RelativeToTerrain& self){
                return nb::str(nb::cast(ecitygml::RelativeToTerrain::Value(self)));
            });
}

} 