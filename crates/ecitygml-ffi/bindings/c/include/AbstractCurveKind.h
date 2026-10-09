#ifndef AbstractCurveKind_H
#define AbstractCurveKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryKind.d.h"
#include "CodeIterator.d.h"
#include "Envelope.d.h"
#include "GeometryType.d.h"
#include "Id.d.h"

#include "AbstractCurveKind.d.h"






const Id* ecitygml_AbstractCurveKind_id(const AbstractCurveKind* self);

CodeIterator* ecitygml_AbstractCurveKind_names(const AbstractCurveKind* self);

const AbstractCurveKind* ecitygml_AbstractCurveKind_try_from(const AbstractGeometryKind* geometry);

GeometryType ecitygml_AbstractCurveKind_geometry_type(const AbstractCurveKind* self);

double ecitygml_AbstractCurveKind_length_3d(const AbstractCurveKind* self);

Envelope* ecitygml_AbstractCurveKind_compute_envelope(const AbstractCurveKind* self);

void ecitygml_AbstractCurveKind_destroy(AbstractCurveKind* self);





#endif // AbstractCurveKind_H
