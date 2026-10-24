#include "diplomat_nanobind_common.hpp"


#include "TrafficSpaceReference.hpp"

namespace ecitygml {
void add_TrafficSpaceReference_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TrafficSpaceReference_slots[] = {
        {Py_tp_free, (void *)ecitygml::TrafficSpaceReference::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TrafficSpaceReference> opaque(mod, "TrafficSpaceReference", nb::type_slots(ecitygml_TrafficSpaceReference_slots), "A reference to a traffic space by `xlink:href`, borrowed from a city model. Like in Rust, it\nhas no accessors of its own: convert it with `Reference::from_traffic_space_reference`.");
}

} 