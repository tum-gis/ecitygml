#include "diplomat_nanobind_common.hpp"


#include "CityModel.hpp"
#include "CitygmlFormat.hpp"
#include "Formatting.hpp"
#include "GmlWriter.hpp"

namespace ecitygml {
void add_GmlWriter_binding(nb::module_ mod) {
    PyType_Slot ecitygml_GmlWriter_slots[] = {
        {Py_tp_free, (void *)ecitygml::GmlWriter::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::GmlWriter> opaque(mod, "GmlWriter", nb::type_slots(ecitygml_GmlWriter_slots), "Writes CityGML to a file or to memory. Rust's builder methods take the writer by value and\n`finish` consumes it, which Diplomat can't express: here they modify it in place, and\n`finish` can be called only once.");
    opaque
        .def("finish", std::move(maybe_op_unwrap(&ecitygml::GmlWriter::finish)), "city_model"_a, "Writes the city model; fails with `InvalidArgument` if called a second time.")
        .def_static("from_base_path_with_format", std::move(maybe_op_unwrap(&ecitygml::GmlWriter::from_base_path_with_format)), "base_path"_a, "format"_a, "Creates (or truncates) the file `<base_path>.<extension of format>`.")
        .def_static("from_path", std::move(maybe_op_unwrap(&ecitygml::GmlWriter::from_path)), "path"_a, "Creates (or truncates) the file at `path`; its extension (`.gml`, `.gml.gz` or\n`.gml.zst`) sets the format.")
        .def("with_formatting", &ecitygml::GmlWriter::with_formatting, "formatting"_a, "How the GML is laid out (default: `Formatting::new_line`). Has no effect after `finish`.");
}

} 