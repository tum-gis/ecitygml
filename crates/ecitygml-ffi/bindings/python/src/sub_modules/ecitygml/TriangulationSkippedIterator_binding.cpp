#include "diplomat_nanobind_common.hpp"


#include "TriangulationSkippedIterator.hpp"

namespace ecitygml {
void add_TriangulationSkippedIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_TriangulationSkippedIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::TriangulationSkippedIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::TriangulationSkippedIterator> opaque(mod, "TriangulationSkippedIterator", nb::type_slots(ecitygml_TriangulationSkippedIterator_slots), "Iterates over the errors of skipped members, borrowed from a triangulation.");
    opaque
        .def("__next__", [](ecitygml::TriangulationSkippedIterator& self){
                auto next = map_inner(self.next());
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            })
            .def("__iter__", [](nb::handle self) { return self; });
}

} 