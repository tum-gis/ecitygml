#include "diplomat_nanobind_common.hpp"


#include "BuildingUsageValueIterator.hpp"

namespace ecitygml {
void add_BuildingUsageValueIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_BuildingUsageValueIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::BuildingUsageValueIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::BuildingUsageValueIterator> opaque(mod, "BuildingUsageValueIterator", nb::type_slots(ecitygml_BuildingUsageValueIterator_slots), "Iterates over a list of code-list values, borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::BuildingUsageValueIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 