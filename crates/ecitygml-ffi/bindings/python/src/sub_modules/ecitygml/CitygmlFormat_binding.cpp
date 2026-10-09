#include "diplomat_nanobind_common.hpp"


#include "CitygmlFormat.hpp"

namespace ecitygml {
void add_CitygmlFormat_binding(nb::module_ mod) {
    nb::class_<ecitygml::CitygmlFormat> e_class(mod, "CitygmlFormat", "Encoding of CityGML content.");
    
        nb::enum_<ecitygml::CitygmlFormat::Value> enumerator(e_class, "CitygmlFormat");
        enumerator
            .value("Gml", ecitygml::CitygmlFormat::Gml, "Plain GML (`.gml`, `.xml`).")
            .value("GmlZst", ecitygml::CitygmlFormat::GmlZst, "Zstandard-compressed GML (`.gml.zst`).")
            .value("GmlGz", ecitygml::CitygmlFormat::GmlGz, "Gzip-compressed GML (`.gml.gz`).")
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::CitygmlFormat::Value>())
            .def(nb::self == ecitygml::CitygmlFormat::Value())
            .def("__repr__", [](const ecitygml::CitygmlFormat& self){
                return nb::str(nb::cast(ecitygml::CitygmlFormat::Value(self)));
            });
}

} 