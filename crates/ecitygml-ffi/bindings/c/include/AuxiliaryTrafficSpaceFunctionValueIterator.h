#ifndef AuxiliaryTrafficSpaceFunctionValueIterator_H
#define AuxiliaryTrafficSpaceFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficSpaceFunctionValue.d.h"

#include "AuxiliaryTrafficSpaceFunctionValueIterator.d.h"






const AuxiliaryTrafficSpaceFunctionValue* ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next(AuxiliaryTrafficSpaceFunctionValueIterator* self);

void ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy(AuxiliaryTrafficSpaceFunctionValueIterator* self);





#endif // AuxiliaryTrafficSpaceFunctionValueIterator_H
