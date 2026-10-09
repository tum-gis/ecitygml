#ifndef PolygonPatch_H
#define PolygonPatch_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractRingKind.d.h"
#include "AbstractRingKindIterator.d.h"
#include "AbstractSurfacePatchKind.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Triangulation.d.h"

#include "PolygonPatch.d.h"






typedef struct ecitygml_PolygonPatch_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_PolygonPatch_triangulate_result;
ecitygml_PolygonPatch_triangulate_result ecitygml_PolygonPatch_triangulate(const PolygonPatch* self);

const PolygonPatch* ecitygml_PolygonPatch_try_from(const AbstractSurfacePatchKind* patch);

const AbstractRingKind* ecitygml_PolygonPatch_exterior(const PolygonPatch* self);

AbstractRingKindIterator* ecitygml_PolygonPatch_interior(const PolygonPatch* self);

typedef struct ecitygml_PolygonPatch_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_PolygonPatch_area_3d_result;
ecitygml_PolygonPatch_area_3d_result ecitygml_PolygonPatch_area_3d(const PolygonPatch* self);

DirectPositionIterator* ecitygml_PolygonPatch_points(const PolygonPatch* self);

Envelope* ecitygml_PolygonPatch_compute_envelope(const PolygonPatch* self);

void ecitygml_PolygonPatch_destroy(PolygonPatch* self);





#endif // PolygonPatch_H
