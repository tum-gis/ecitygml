#include "diplomat_nanobind_common.hpp"


#include "ExternalReferenceIterator.hpp"

namespace ecitygml {
void add_ExternalReferenceIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_ExternalReferenceIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::ExternalReferenceIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::ExternalReferenceIterator> opaque(mod, "ExternalReferenceIterator", nb::type_slots(ecitygml_ExternalReferenceIterator_slots), "Iterates over external references, borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::ExternalReferenceIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 