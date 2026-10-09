#ifndef MultiCurve_H
#define MultiCurve_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCurvePropertyIterator.d.h"
#include "AbstractGeometryKind.d.h"
#include "CodeIterator.d.h"
#include "Envelope.d.h"
#include "Error.d.h"
#include "Id.d.h"

#include "MultiCurve.d.h"






const Id* ecitygml_MultiCurve_id(const MultiCurve* self);

CodeIterator* ecitygml_MultiCurve_names(const MultiCurve* self);

const MultiCurve* ecitygml_MultiCurve_try_from(const AbstractGeometryKind* geometry);

AbstractCurvePropertyIterator* ecitygml_MultiCurve_curve_member(const MultiCurve* self);

typedef struct ecitygml_MultiCurve_length_3d_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_MultiCurve_length_3d_result;
ecitygml_MultiCurve_length_3d_result ecitygml_MultiCurve_length_3d(const MultiCurve* self);

Envelope* ecitygml_MultiCurve_compute_envelope(const MultiCurve* self);

void ecitygml_MultiCurve_destroy(MultiCurve* self);





#endif // MultiCurve_H
