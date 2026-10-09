#ifndef TriangulatedSurface_H
#define TriangulatedSurface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfaceKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"
#include "Surface.d.h"
#include "TriangleIterator.d.h"

#include "TriangulatedSurface.d.h"






const Id* ecitygml_TriangulatedSurface_id(const TriangulatedSurface* self);

CodeIterator* ecitygml_TriangulatedSurface_names(const TriangulatedSurface* self);

const TriangulatedSurface* ecitygml_TriangulatedSurface_try_from(const AbstractSurfaceKind* surface);

TriangleIterator* ecitygml_TriangulatedSurface_triangles(const TriangulatedSurface* self);

const Surface* ecitygml_TriangulatedSurface_surface(const TriangulatedSurface* self);

DirectPositionIterator* ecitygml_TriangulatedSurface_points(const TriangulatedSurface* self);

typedef struct ecitygml_TriangulatedSurface_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_TriangulatedSurface_area_3d_result;
ecitygml_TriangulatedSurface_area_3d_result ecitygml_TriangulatedSurface_area_3d(const TriangulatedSurface* self);

Envelope* ecitygml_TriangulatedSurface_compute_envelope(const TriangulatedSurface* self);

void ecitygml_TriangulatedSurface_destroy(TriangulatedSurface* self);





#endif // TriangulatedSurface_H
