#include "diplomat_nanobind_common.hpp"


#include "DirectPosition.hpp"
#include "Envelope.hpp"

namespace ecitygml {
void add_Envelope_binding(nb::module_ mod) {
    PyType_Slot ecitygml_Envelope_slots[] = {
        {Py_tp_free, (void *)ecitygml::Envelope::operator delete },
        {Py_tp_dealloc, (void *)diplomat_tp_dealloc},
        {0, nullptr}};
    
    nb::class_<ecitygml::Envelope> opaque(mod, "Envelope", nb::type_slots(ecitygml_Envelope_slots), "An axis-aligned bounding box, borrowed from a city model.");
    opaque
        .def("contains", &ecitygml::Envelope::contains, "point"_a, "Whether `point` lies inside or on the boundary of the box.")
        .def("lower_corner", &ecitygml::Envelope::lower_corner, nb::rv_policy::reference_internal)
        .def("size_x", &ecitygml::Envelope::size_x, "Extent along the x axis.")
        .def("size_y", &ecitygml::Envelope::size_y, "Extent along the y axis.")
        .def("size_z", &ecitygml::Envelope::size_z, "Extent along the z axis.")
        .def("upper_corner", &ecitygml::Envelope::upper_corner, nb::rv_policy::reference_internal)
        .def("volume", &ecitygml::Envelope::volume, "Volume of the box (`size_x * size_y * size_z`); `0.0` if an extent is zero.");
}

} 