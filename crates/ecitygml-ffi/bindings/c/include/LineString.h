#ifndef LineString_H
#define LineString_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCurveKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Id.d.h"

#include "LineString.d.h"






const Id* ecitygml_LineString_id(const LineString* self);

CodeIterator* ecitygml_LineString_names(const LineString* self);

const LineString* ecitygml_LineString_try_from(const AbstractCurveKind* curve);

DirectPositionIterator* ecitygml_LineString_points(const LineString* self);

double ecitygml_LineString_length_3d(const LineString* self);

Envelope* ecitygml_LineString_compute_envelope(const LineString* self);

void ecitygml_LineString_destroy(LineString* self);





#endif // LineString_H
