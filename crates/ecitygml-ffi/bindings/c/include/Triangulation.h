#ifndef Triangulation_H
#define Triangulation_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TriangulatedSurface.d.h"
#include "TriangulationSkippedIterator.d.h"

#include "Triangulation.d.h"






const TriangulatedSurface* ecitygml_Triangulation_surface(const Triangulation* self);

bool ecitygml_Triangulation_has_skipped(const Triangulation* self);

TriangulationSkippedIterator* ecitygml_Triangulation_skipped(const Triangulation* self);

void ecitygml_Triangulation_destroy(Triangulation* self);





#endif // Triangulation_H
