#ifndef AbstractSurfacePatchKind_H
#define AbstractSurfacePatchKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Triangulation.d.h"

#include "AbstractSurfacePatchKind.d.h"






typedef struct ecitygml_AbstractSurfacePatchKind_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_AbstractSurfacePatchKind_triangulate_result;
ecitygml_AbstractSurfacePatchKind_triangulate_result ecitygml_AbstractSurfacePatchKind_triangulate(const AbstractSurfacePatchKind* self);

typedef struct ecitygml_AbstractSurfacePatchKind_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_AbstractSurfacePatchKind_area_3d_result;
ecitygml_AbstractSurfacePatchKind_area_3d_result ecitygml_AbstractSurfacePatchKind_area_3d(const AbstractSurfacePatchKind* self);

DirectPositionIterator* ecitygml_AbstractSurfacePatchKind_points(const AbstractSurfacePatchKind* self);

Envelope* ecitygml_AbstractSurfacePatchKind_compute_envelope(const AbstractSurfacePatchKind* self);

void ecitygml_AbstractSurfacePatchKind_destroy(AbstractSurfacePatchKind* self);





#endif // AbstractSurfacePatchKind_H
