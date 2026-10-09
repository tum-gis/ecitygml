#include "diplomat_nanobind_common.hpp"


#include "TunnelPartPropertyIterator.hpp"

namespace ecitygml {
void add_TunnelPartPropertyIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TunnelPartPropertyIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::TunnelPartPropertyIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TunnelPartPropertyIterator> opaque(mod, "TunnelPartPropertyIterator", nb::type_slots(ecitygml_TunnelPartPropertyIterator_slots), "Iterates over tunnel part properties, borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::TunnelPartPropertyIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 