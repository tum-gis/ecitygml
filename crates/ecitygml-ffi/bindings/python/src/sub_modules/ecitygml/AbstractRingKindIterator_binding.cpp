#include "diplomat_nanobind_common.hpp"


#include "AbstractRingKindIterator.hpp"

namespace ecitygml {
void add_AbstractRingKindIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractRingKindIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractRingKindIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractRingKindIterator> opaque(mod, "AbstractRingKindIterator", nb::type_slots(ecitygml_AbstractRingKindIterator_slots), "Iterates over rings (e.g. a polygon's interior rings), borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::AbstractRingKindIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 