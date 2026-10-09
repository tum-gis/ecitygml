#ifndef ecitygml_GeometryType_D_HPP
#define ecitygml_GeometryType_D_HPP

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
    enum GeometryType {
      GeometryType_Point = 0,
      GeometryType_LineString = 1,
      GeometryType_Curve = 2,
      GeometryType_OrientableCurve = 3,
      GeometryType_LinearRing = 4,
      GeometryType_Ring = 5,
      GeometryType_Polygon = 6,
      GeometryType_Surface = 7,
      GeometryType_OrientableSurface = 8,
      GeometryType_PolyhedralSurface = 9,
      GeometryType_TriangulatedSurface = 10,
      GeometryType_Tin = 11,
      GeometryType_Shell = 12,
      GeometryType_Solid = 13,
      GeometryType_MultiGeometry = 14,
      GeometryType_MultiPoint = 15,
      GeometryType_MultiCurve = 16,
      GeometryType_MultiSurface = 17,
      GeometryType_MultiSolid = 18,
      GeometryType_GeometricComplex = 19,
      GeometryType_CompositeCurve = 20,
      GeometryType_CompositeSurface = 21,
      GeometryType_CompositeSolid = 22,
      GeometryType_Grid = 23,
      GeometryType_RectifiedGrid = 24,
    };

    typedef struct GeometryType_option {union { GeometryType ok; }; bool is_ok; } GeometryType_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Type of a GML geometry.
 */
class GeometryType {
public:
    enum Value {
        Point = 0,
        LineString = 1,
        Curve = 2,
        OrientableCurve = 3,
        LinearRing = 4,
        Ring = 5,
        Polygon = 6,
        Surface = 7,
        OrientableSurface = 8,
        PolyhedralSurface = 9,
        TriangulatedSurface = 10,
        Tin = 11,
        Shell = 12,
        Solid = 13,
        MultiGeometry = 14,
        MultiPoint = 15,
        MultiCurve = 16,
        MultiSurface = 17,
        MultiSolid = 18,
        GeometricComplex = 19,
        CompositeCurve = 20,
        CompositeSurface = 21,
        CompositeSolid = 22,
        Grid = 23,
        RectifiedGrid = 24,
    };

    GeometryType(): value(Value::Point) {}

    // Implicit conversions between enum and ::Value
    constexpr GeometryType(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::GeometryType AsFFI() const;
    inline static ecitygml::GeometryType FromFFI(ecitygml::capi::GeometryType c_enum);
private:
    Value value;
};

} // namespace
#endif // ecitygml_GeometryType_D_HPP
