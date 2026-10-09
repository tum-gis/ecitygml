#ifndef CompositeSurface_H
#define CompositeSurface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfaceKind.d.h"
#include "AbstractSurfacePropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "CompositeSurface.d.h"






const Id* ecitygml_CompositeSurface_id(const CompositeSurface* self);

CodeIterator* ecitygml_CompositeSurface_names(const CompositeSurface* self);

typedef struct ecitygml_CompositeSurface_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_CompositeSurface_triangulate_result;
ecitygml_CompositeSurface_triangulate_result ecitygml_CompositeSurface_triangulate(const CompositeSurface* self);

const CompositeSurface* ecitygml_CompositeSurface_try_from(const AbstractSurfaceKind* surface);

AbstractSurfacePropertyIterator* ecitygml_CompositeSurface_surface_member(const CompositeSurface* self);

typedef struct ecitygml_CompositeSurface_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_CompositeSurface_area_3d_result;
ecitygml_CompositeSurface_area_3d_result ecitygml_CompositeSurface_area_3d(const CompositeSurface* self);

DirectPositionIterator* ecitygml_CompositeSurface_points(const CompositeSurface* self);

Envelope* ecitygml_CompositeSurface_compute_envelope(const CompositeSurface* self);

void ecitygml_CompositeSurface_destroy(CompositeSurface* self);





#endif // CompositeSurface_H
