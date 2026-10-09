#ifndef AuxiliaryTrafficAreaFunctionValueIterator_H
#define AuxiliaryTrafficAreaFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficAreaFunctionValue.d.h"

#include "AuxiliaryTrafficAreaFunctionValueIterator.d.h"






const AuxiliaryTrafficAreaFunctionValue* ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_next(AuxiliaryTrafficAreaFunctionValueIterator* self);

void ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_destroy(AuxiliaryTrafficAreaFunctionValueIterator* self);





#endif // AuxiliaryTrafficAreaFunctionValueIterator_H
