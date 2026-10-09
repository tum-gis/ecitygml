#ifndef Shell_H
#define Shell_H

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

#include "Shell.d.h"






const Id* ecitygml_Shell_id(const Shell* self);

CodeIterator* ecitygml_Shell_names(const Shell* self);

typedef struct ecitygml_Shell_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_Shell_triangulate_result;
ecitygml_Shell_triangulate_result ecitygml_Shell_triangulate(const Shell* self);

const Shell* ecitygml_Shell_try_from(const AbstractSurfaceKind* surface);

AbstractSurfacePropertyIterator* ecitygml_Shell_members(const Shell* self);

DirectPositionIterator* ecitygml_Shell_points(const Shell* self);

typedef struct ecitygml_Shell_area_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_Shell_area_3d_result;
ecitygml_Shell_area_3d_result ecitygml_Shell_area_3d(const Shell* self);

typedef struct ecitygml_Shell_volume_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_Shell_volume_3d_result;
ecitygml_Shell_volume_3d_result ecitygml_Shell_volume_3d(const Shell* self);

Envelope* ecitygml_Shell_compute_envelope(const Shell* self);

void ecitygml_Shell_destroy(Shell* self);





#endif // Shell_H
