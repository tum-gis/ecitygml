#ifndef Solid_H
#define Solid_H

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
#include "Id.d.h"
#include "Shell.d.h"
#include "ShellIterator.d.h"
#include "Triangulation.d.h"

#include "Solid.d.h"






const Id* ecitygml_Solid_id(const Solid* self);

CodeIterator* ecitygml_Solid_names(const Solid* self);

typedef struct ecitygml_Solid_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_Solid_triangulate_result;
ecitygml_Solid_triangulate_result ecitygml_Solid_triangulate(const Solid* self);

const Solid* ecitygml_Solid_try_from(const AbstractGeometryKind* geometry);

const Shell* ecitygml_Solid_exterior(const Solid* self);

ShellIterator* ecitygml_Solid_interior(const Solid* self);

typedef struct ecitygml_Solid_volume_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_Solid_volume_3d_result;
ecitygml_Solid_volume_3d_result ecitygml_Solid_volume_3d(const Solid* self);

Envelope* ecitygml_Solid_compute_envelope(const Solid* self);

DirectPositionIterator* ecitygml_Solid_points(const Solid* self);

void ecitygml_Solid_destroy(Solid* self);





#endif // Solid_H
