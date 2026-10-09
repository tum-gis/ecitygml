#ifndef Polygon_H
#define Polygon_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractRingKind.d.h"
#include "AbstractRingKindIterator.d.h"
#include "AbstractSurfaceKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "Polygon.d.h"






const Id* ecitygml_Polygon_id(const Polygon* self);

CodeIterator* ecitygml_Polygon_names(const Polygon* self);

typedef struct ecitygml_Polygon_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_Polygon_triangulate_result;
ecitygml_Polygon_triangulate_result ecitygml_Polygon_triangulate(const Polygon* self);

const Polygon* ecitygml_Polygon_try_from(const AbstractSurfaceKind* surface);

const AbstractRingKind* ecitygml_Polygon_exterior(const Polygon* self);

AbstractRingKindIterator* ecitygml_Polygon_interior(const Polygon* self);

typedef struct ecitygml_Polygon_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_Polygon_area_3d_result;
ecitygml_Polygon_area_3d_result ecitygml_Polygon_area_3d(const Polygon* self);

DirectPositionIterator* ecitygml_Polygon_points(const Polygon* self);

Envelope* ecitygml_Polygon_compute_envelope(const Polygon* self);

void ecitygml_Polygon_destroy(Polygon* self);





#endif // Polygon_H
