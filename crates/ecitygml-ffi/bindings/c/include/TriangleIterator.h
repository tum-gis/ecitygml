#ifndef TriangleIterator_H
#define TriangleIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Triangle.d.h"

#include "TriangleIterator.d.h"






const Triangle* ecitygml_TriangleIterator_next(TriangleIterator* self);

void ecitygml_TriangleIterator_destroy(TriangleIterator* self);





#endif // TriangleIterator_H
