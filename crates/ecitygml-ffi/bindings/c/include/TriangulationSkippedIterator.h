#ifndef TriangulationSkippedIterator_H
#define TriangulationSkippedIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Error.d.h"

#include "TriangulationSkippedIterator.d.h"






Error* ecitygml_TriangulationSkippedIterator_next(TriangulationSkippedIterator* self);

void ecitygml_TriangulationSkippedIterator_destroy(TriangulationSkippedIterator* self);





#endif // TriangulationSkippedIterator_H
