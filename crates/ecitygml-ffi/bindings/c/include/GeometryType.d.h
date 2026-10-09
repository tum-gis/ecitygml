#ifndef GeometryType_D_H
#define GeometryType_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum GeometryType {
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
} GeometryType;

typedef struct GeometryType_option {union { GeometryType ok; }; bool is_ok; } GeometryType_option;



#endif // GeometryType_D_H
