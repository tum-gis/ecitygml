#ifndef AbstractRingKind_H
#define AbstractRingKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCurveKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "GeometryType.d.h"
#include "Id.d.h"

#include "AbstractRingKind.d.h"






const Id* ecitygml_AbstractRingKind_id(const AbstractRingKind* self);

CodeIterator* ecitygml_AbstractRingKind_names(const AbstractRingKind* self);

const AbstractRingKind* ecitygml_AbstractRingKind_try_from(const AbstractCurveKind* curve);

GeometryType ecitygml_AbstractRingKind_geometry_type(const AbstractRingKind* self);

DirectPositionIterator* ecitygml_AbstractRingKind_points(const AbstractRingKind* self);

double ecitygml_AbstractRingKind_length_3d(const AbstractRingKind* self);

double ecitygml_AbstractRingKind_area_3d(const AbstractRingKind* self);

Envelope* ecitygml_AbstractRingKind_compute_envelope(const AbstractRingKind* self);

void ecitygml_AbstractRingKind_destroy(AbstractRingKind* self);





#endif // AbstractRingKind_H
