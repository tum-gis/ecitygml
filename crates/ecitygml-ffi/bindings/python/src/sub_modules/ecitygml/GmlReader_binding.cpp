#include "diplomat_nanobind_common.hpp"


#include "CitygmlFormat.hpp"
#include "GmlReader.hpp"

namespace ecitygml {
void add_GmlReader_binding(nb::module_ mod) {
    PyType_Slot ecitygml_GmlReader_slots[] = {
        {Py_tp_free, (void *)ecitygml::GmlReader::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::GmlReader> opaque(mod, "GmlReader", nb::type_slots(ecitygml_GmlReader_slots), "Reads CityGML from a file or from memory. Rust's builder methods take the reader by value,\nwhich Diplomat can't express: here they modify it in place, and `finish` can be called only once.");
    opaque
        .def(nb::new_(std::move(maybe_op_unwrap(&ecitygml::GmlReader::new_))), "data"_a, "format"_a, "Reads CityGML content of the given `format` from memory, e.g. in WebAssembly, where there is\nno file system. The data is copied.")
        .def("finish", std::move(maybe_op_unwrap(&ecitygml::GmlReader::finish)), "Reads the city model; fails with `InvalidArgument` if called a second time.")
        .def_static("from_path", std::move(maybe_op_unwrap(&ecitygml::GmlReader::from_path)), "path"_a, "Opens the CityGML file at `path` (`.gml`, `.gml.gz` or `.gml.zst`).")
        .def("with_rebuild_object_bounds", &ecitygml::GmlReader::with_rebuild_object_bounds, "rebuild_object_bounds"_a, "Whether envelopes of child objects are recomputed from their geometry (default: true).\nHas no effect after `finish`.");
}

} 