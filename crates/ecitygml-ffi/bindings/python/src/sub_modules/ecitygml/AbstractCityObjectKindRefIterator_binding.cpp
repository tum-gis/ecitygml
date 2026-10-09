#include "diplomat_nanobind_common.hpp"


#include "AbstractCityObjectKindRefIterator.hpp"

namespace ecitygml {
void add_AbstractCityObjectKindRefIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractCityObjectKindRefIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractCityObjectKindRefIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractCityObjectKindRefIterator> opaque(mod, "AbstractCityObjectKindRefIterator", nb::type_slots(ecitygml_AbstractCityObjectKindRefIterator_slots), "Iterates over city objects of a city model, which it borrows.");
    opaque
        .def("__next__", [](ecitygml::AbstractCityObjectKindRefIterator& self){
                auto next = map_inner(self.next());
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>())
            .def("__iter__", [](nb::handle self) { return self; });
}

} 