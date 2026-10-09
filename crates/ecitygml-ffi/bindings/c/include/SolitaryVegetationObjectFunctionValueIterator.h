#ifndef SolitaryVegetationObjectFunctionValueIterator_H
#define SolitaryVegetationObjectFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "SolitaryVegetationObjectFunctionValue.d.h"

#include "SolitaryVegetationObjectFunctionValueIterator.d.h"






const SolitaryVegetationObjectFunctionValue* ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(SolitaryVegetationObjectFunctionValueIterator* self);

void ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(SolitaryVegetationObjectFunctionValueIterator* self);





#endif // SolitaryVegetationObjectFunctionValueIterator_H
