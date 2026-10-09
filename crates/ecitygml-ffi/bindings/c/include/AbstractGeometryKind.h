#ifndef AbstractGeometryKind_H
#define AbstractGeometryKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CodeIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "GeometryType.d.h"
#include "Id.d.h"
#include "Triangulation.d.h"

#include "AbstractGeometryKind.d.h"






const Id* ecitygml_AbstractGeometryKind_id(const AbstractGeometryKind* self);

CodeIterator* ecitygml_AbstractGeometryKind_names(const AbstractGeometryKind* self);

typedef struct ecitygml_AbstractGeometryKind_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_AbstractGeometryKind_triangulate_result;
ecitygml_AbstractGeometryKind_triangulate_result ecitygml_AbstractGeometryKind_triangulate(const AbstractGeometryKind* self);

GeometryType ecitygml_AbstractGeometryKind_geometry_type(const AbstractGeometryKind* self);

Envelope* ecitygml_AbstractGeometryKind_compute_envelope(const AbstractGeometryKind* self);

void ecitygml_AbstractGeometryKind_destroy(AbstractGeometryKind* self);





#endif // AbstractGeometryKind_H
