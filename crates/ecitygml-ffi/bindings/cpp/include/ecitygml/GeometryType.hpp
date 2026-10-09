#ifndef ecitygml_GeometryType_HPP
#define ecitygml_GeometryType_HPP

#include "GeometryType.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {

} // namespace capi
} // namespace

inline ecitygml::capi::GeometryType ecitygml::GeometryType::AsFFI() const {
    return static_cast<ecitygml::capi::GeometryType>(value);
}

inline ecitygml::GeometryType ecitygml::GeometryType::FromFFI(ecitygml::capi::GeometryType c_enum) {
    switch (c_enum) {
        case ecitygml::capi::GeometryType_Point:
        case ecitygml::capi::GeometryType_LineString:
        case ecitygml::capi::GeometryType_Curve:
        case ecitygml::capi::GeometryType_OrientableCurve:
        case ecitygml::capi::GeometryType_LinearRing:
        case ecitygml::capi::GeometryType_Ring:
        case ecitygml::capi::GeometryType_Polygon:
        case ecitygml::capi::GeometryType_Surface:
        case ecitygml::capi::GeometryType_OrientableSurface:
        case ecitygml::capi::GeometryType_PolyhedralSurface:
        case ecitygml::capi::GeometryType_TriangulatedSurface:
        case ecitygml::capi::GeometryType_Tin:
        case ecitygml::capi::GeometryType_Shell:
        case ecitygml::capi::GeometryType_Solid:
        case ecitygml::capi::GeometryType_MultiGeometry:
        case ecitygml::capi::GeometryType_MultiPoint:
        case ecitygml::capi::GeometryType_MultiCurve:
        case ecitygml::capi::GeometryType_MultiSurface:
        case ecitygml::capi::GeometryType_MultiSolid:
        case ecitygml::capi::GeometryType_GeometricComplex:
        case ecitygml::capi::GeometryType_CompositeCurve:
        case ecitygml::capi::GeometryType_CompositeSurface:
        case ecitygml::capi::GeometryType_CompositeSolid:
        case ecitygml::capi::GeometryType_Grid:
        case ecitygml::capi::GeometryType_RectifiedGrid:
            return static_cast<ecitygml::GeometryType::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_GeometryType_HPP
