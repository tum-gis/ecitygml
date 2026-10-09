#include "diplomat_nanobind_common.hpp"


#include "GeometryType.hpp"

namespace ecitygml {
void add_GeometryType_binding(nb::module_ mod) {
    nb::class_<ecitygml::GeometryType> e_class(mod, "GeometryType", "Type of a GML geometry.");
    
        nb::enum_<ecitygml::GeometryType::Value> enumerator(e_class, "GeometryType");
        enumerator
            .value("Point", ecitygml::GeometryType::Point)
            .value("LineString", ecitygml::GeometryType::LineString)
            .value("Curve", ecitygml::GeometryType::Curve)
            .value("OrientableCurve", ecitygml::GeometryType::OrientableCurve)
            .value("LinearRing", ecitygml::GeometryType::LinearRing)
            .value("Ring", ecitygml::GeometryType::Ring)
            .value("Polygon", ecitygml::GeometryType::Polygon)
            .value("Surface", ecitygml::GeometryType::Surface)
            .value("OrientableSurface", ecitygml::GeometryType::OrientableSurface)
            .value("PolyhedralSurface", ecitygml::GeometryType::PolyhedralSurface)
            .value("TriangulatedSurface", ecitygml::GeometryType::TriangulatedSurface)
            .value("Tin", ecitygml::GeometryType::Tin)
            .value("Shell", ecitygml::GeometryType::Shell)
            .value("Solid", ecitygml::GeometryType::Solid)
            .value("MultiGeometry", ecitygml::GeometryType::MultiGeometry)
            .value("MultiPoint", ecitygml::GeometryType::MultiPoint)
            .value("MultiCurve", ecitygml::GeometryType::MultiCurve)
            .value("MultiSurface", ecitygml::GeometryType::MultiSurface)
            .value("MultiSolid", ecitygml::GeometryType::MultiSolid)
            .value("GeometricComplex", ecitygml::GeometryType::GeometricComplex)
            .value("CompositeCurve", ecitygml::GeometryType::CompositeCurve)
            .value("CompositeSurface", ecitygml::GeometryType::CompositeSurface)
            .value("CompositeSolid", ecitygml::GeometryType::CompositeSolid)
            .value("Grid", ecitygml::GeometryType::Grid)
            .value("RectifiedGrid", ecitygml::GeometryType::RectifiedGrid)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::GeometryType::Value>())
            .def(nb::self == ecitygml::GeometryType::Value())
            .def("__repr__", [](const ecitygml::GeometryType& self){
                return nb::str(nb::cast(ecitygml::GeometryType::Value(self)));
            });
}

} 