#include "diplomat_nanobind_common.hpp"


#include "AbstractSpaceBoundaryPropertyIterator.hpp"

namespace ecitygml {
void add_AbstractSpaceBoundaryPropertyIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSpaceBoundaryPropertyIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSpaceBoundaryPropertyIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSpaceBoundaryPropertyIterator> opaque(mod, "AbstractSpaceBoundaryPropertyIterator", nb::type_slots(ecitygml_AbstractSpaceBoundaryPropertyIterator_slots), "Iterates over space boundary properties, borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::AbstractSpaceBoundaryPropertyIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 