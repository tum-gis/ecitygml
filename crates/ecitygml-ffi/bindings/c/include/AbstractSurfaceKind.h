#ifndef AbstractSurfaceKind_H
#define AbstractSurfaceKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "GeometryType.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "AbstractSurfaceKind.d.h"






const Id* ecitygml_AbstractSurfaceKind_id(const AbstractSurfaceKind* self);

CodeIterator* ecitygml_AbstractSurfaceKind_names(const AbstractSurfaceKind* self);

typedef struct ecitygml_AbstractSurfaceKind_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_AbstractSurfaceKind_triangulate_result;
ecitygml_AbstractSurfaceKind_triangulate_result ecitygml_AbstractSurfaceKind_triangulate(const AbstractSurfaceKind* self);

const AbstractSurfaceKind* ecitygml_AbstractSurfaceKind_try_from(const AbstractGeometryKind* geometry);

GeometryType ecitygml_AbstractSurfaceKind_geometry_type(const AbstractSurfaceKind* self);

typedef struct ecitygml_AbstractSurfaceKind_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_AbstractSurfaceKind_area_3d_result;
ecitygml_AbstractSurfaceKind_area_3d_result ecitygml_AbstractSurfaceKind_area_3d(const AbstractSurfaceKind* self);

DirectPositionIterator* ecitygml_AbstractSurfaceKind_points(const AbstractSurfaceKind* self);

Envelope* ecitygml_AbstractSurfaceKind_compute_envelope(const AbstractSurfaceKind* self);

void ecitygml_AbstractSurfaceKind_destroy(AbstractSurfaceKind* self);





#endif // AbstractSurfaceKind_H
