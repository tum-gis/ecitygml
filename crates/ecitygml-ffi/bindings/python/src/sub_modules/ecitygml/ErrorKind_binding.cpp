#include "diplomat_nanobind_common.hpp"


#include "ErrorKind.hpp"

namespace ecitygml {
void add_ErrorKind_binding(nb::module_ mod) {
    nb::class_<ecitygml::ErrorKind> e_class(mod, "ErrorKind", "Category of an [Error].");
    
        nb::enum_<ecitygml::ErrorKind::Value> enumerator(e_class, "ErrorKind");
        enumerator
            .value("InvalidArgument", ecitygml::ErrorKind::InvalidArgument, "An argument is invalid, e.g. an unsupported file extension or a non-UTF-8 string.")
            .value("Io", ecitygml::ErrorKind::Io, "Reading a file failed.")
            .value("Parse", ecitygml::ErrorKind::Parse, "The file content is not valid CityGML.")
            .value("UnresolvedReference", ecitygml::ErrorKind::UnresolvedReference, "Geometry is only referenced by `xlink:href` and the reference is not resolved.")
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::ErrorKind::Value>())
            .def(nb::self == ecitygml::ErrorKind::Value())
            .def("__repr__", [](const ecitygml::ErrorKind& self){
                return nb::str(nb::cast(ecitygml::ErrorKind::Value(self)));
            });
}

} 