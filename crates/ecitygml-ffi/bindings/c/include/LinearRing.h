#ifndef LinearRing_H
#define LinearRing_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractRingKind.d.h"
#include "CodeIterator.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Id.d.h"

#include "LinearRing.d.h"






const Id* ecitygml_LinearRing_id(const LinearRing* self);

CodeIterator* ecitygml_LinearRing_names(const LinearRing* self);

const LinearRing* ecitygml_LinearRing_try_from(const AbstractRingKind* ring);

DirectPositionIterator* ecitygml_LinearRing_points(const LinearRing* self);

double ecitygml_LinearRing_length_3d(const LinearRing* self);

double ecitygml_LinearRing_area_3d(const LinearRing* self);

Envelope* ecitygml_LinearRing_compute_envelope(const LinearRing* self);

void ecitygml_LinearRing_destroy(LinearRing* self);





#endif // LinearRing_H
