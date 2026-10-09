#ifndef Point_H
#define Point_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPosition.d.h"
#include "Envelope.d.h"
#include "Id.d.h"

#include "Point.d.h"






const Id* ecitygml_Point_id(const Point* self);

CodeIterator* ecitygml_Point_names(const Point* self);

const Point* ecitygml_Point_try_from(const AbstractGeometryKind* geometry);

const DirectPosition* ecitygml_Point_pos(const Point* self);

Envelope* ecitygml_Point_compute_envelope(const Point* self);

void ecitygml_Point_destroy(Point* self);





#endif // Point_H
