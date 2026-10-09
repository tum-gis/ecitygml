#include "diplomat_nanobind_common.hpp"


#include "AbstractSurfacePatchKindIterator.hpp"

namespace ecitygml {
void add_AbstractSurfacePatchKindIterator_binding(nb::module_ mod) {
    PyType_Slot ecitygml_AbstractSurfacePatchKindIterator_slots[] = {
        {Py_tp_free, (void *)ecitygml::AbstractSurfacePatchKindIterator::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::AbstractSurfacePatchKindIterator> opaque(mod, "AbstractSurfacePatchKindIterator", nb::type_slots(ecitygml_AbstractSurfacePatchKindIterator_slots), "Iterates over surface patches, borrowed from a city model.");
    opaque
        .def("__next__", [](ecitygml::AbstractSurfacePatchKindIterator& self){
                auto next = self.next();
                if (!next) {
                    throw nb::stop_iteration();
                }
                return next_inner_extractor<decltype(next)>::get(std::move(next));
            }, nb::keep_alive<0, 1>(), nb::rv_policy::reference_internal)
            .def("__iter__", [](nb::handle self) { return self; });
}

} 