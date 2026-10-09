#include "diplomat_nanobind_common.hpp"


#include "AbstractFeatureKindRefIterator.hpp"

namespace ecitygml {
void add_AbstractFeatureKindRefIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractFeatureKindRefIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractFeatureKindRefIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractFeatureKindRefIterator> opaque(mod, "AbstractFeatureKindRefIterator", nb::type_slots(ecitygml_AbstractFeatureKindRefIterator_slots), "Iterates over features of a city model, which it borrows.");
    opaque
        .def("__next__", [](ecitygml::AbstractFeatureKindRefIterator& self){
                auto next = map_inner(self.next());
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>())
            .def("__iter__", [](nb::handle self) { return self; });
}

} 