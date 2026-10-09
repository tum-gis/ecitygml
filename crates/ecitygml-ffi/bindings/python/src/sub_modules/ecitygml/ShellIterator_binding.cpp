#include "diplomat_nanobind_common.hpp"


#include "ShellIterator.hpp"

namespace ecitygml {
void add_ShellIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ShellIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::ShellIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ShellIterator> opaque(mod, "ShellIterator", nb::type_slots(ecitygml_ShellIterator_slots), "Iterates over shells (e.g. a solid's interior shells), borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::ShellIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 