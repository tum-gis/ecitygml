#ifndef Triangle_H
#define Triangle_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractRingKind.d.h"
#include "AbstractSurfacePatchKind.d.h"
#include "DirectPosition.d.h"
#include "DirectPositionIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Triangulation.d.h"

#include "Triangle.d.h"






typedef struct ecitygml_Triangle_triangulate_result {union {Triangulation* ok; Error* err;}; bool is_ok;} ecitygml_Triangle_triangulate_result;
ecitygml_Triangle_triangulate_result ecitygml_Triangle_triangulate(const Triangle* self);

const Triangle* ecitygml_Triangle_try_from(const AbstractSurfacePatchKind* patch);

const AbstractRingKind* ecitygml_Triangle_exterior(const Triangle* self);

const DirectPosition* ecitygml_Triangle_a(const Triangle* self);

const DirectPosition* ecitygml_Triangle_b(const Triangle* self);

const DirectPosition* ecitygml_Triangle_c(const Triangle* self);

double ecitygml_Triangle_area(const Triangle* self);

DirectPositionIterator* ecitygml_Triangle_points(const Triangle* self);

Envelope* ecitygml_Triangle_compute_envelope(const Triangle* self);

void ecitygml_Triangle_destroy(Triangle* self);





#endif // Triangle_H
