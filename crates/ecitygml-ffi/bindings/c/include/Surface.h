#ifndef Surface_H
#define Surface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfaceKind.d.h"
#include "AbstractSurfacePatchKindIterator.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "Surface.d.h"






const Id* ecitygml_Surface_id(const Surface* self);

CodeIterator* ecitygml_Surface_names(const Surface* self);

typedef struct ecitygml_Surface_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_Surface_triangulate_result;
ecitygml_Surface_triangulate_result ecitygml_Surface_triangulate(const Surface* self);

const Surface* ecitygml_Surface_try_from(const AbstractSurfaceKind* surface);

AbstractSurfacePatchKindIterator* ecitygml_Surface_patches(const Surface* self);

typedef struct ecitygml_Surface_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_Surface_area_3d_result;
ecitygml_Surface_area_3d_result ecitygml_Surface_area_3d(const Surface* self);

DirectPositionIterator* ecitygml_Surface_points(const Surface* self);

Envelope* ecitygml_Surface_compute_envelope(const Surface* self);

void ecitygml_Surface_destroy(Surface* self);





#endif // Surface_H
