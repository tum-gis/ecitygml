#ifndef MultiSurface_H
#define MultiSurface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryKind.d.h"
#include "AbstractSurfacePropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "MultiSurface.d.h"






const Id* ecitygml_MultiSurface_id(const MultiSurface* self);

CodeIterator* ecitygml_MultiSurface_names(const MultiSurface* self);

typedef struct ecitygml_MultiSurface_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_MultiSurface_triangulate_result;
ecitygml_MultiSurface_triangulate_result ecitygml_MultiSurface_triangulate(const MultiSurface* self);

const MultiSurface* ecitygml_MultiSurface_try_from(const AbstractGeometryKind* geometry);

AbstractSurfacePropertyIterator* ecitygml_MultiSurface_surface_member(const MultiSurface* self);

typedef struct ecitygml_MultiSurface_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_MultiSurface_area_3d_result;
ecitygml_MultiSurface_area_3d_result ecitygml_MultiSurface_area_3d(const MultiSurface* self);

DirectPositionIterator* ecitygml_MultiSurface_points(const MultiSurface* self);

Envelope* ecitygml_MultiSurface_compute_envelope(const MultiSurface* self);

void ecitygml_MultiSurface_destroy(MultiSurface* self);





#endif // MultiSurface_H
