#include "diplomat_nanobind_common.hpp"


#include "Id.hpp"

namespace ecitygml {
void add_Id_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Id_slots[] = {
        {Py_tp_free, (void *)ecitygml::Id::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Id> opaque(mod, "Id", nb::type_slots(ecitygml_Id_slots), "A `gml:id`, borrowed from a city model.");
    opaque
        .def("as_str", &ecitygml::Id::as_str);
}

} 