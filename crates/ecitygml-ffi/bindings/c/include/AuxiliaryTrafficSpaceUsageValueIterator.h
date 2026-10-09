#ifndef AuxiliaryTrafficSpaceUsageValueIterator_H
#define AuxiliaryTrafficSpaceUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficSpaceUsageValue.d.h"

#include "AuxiliaryTrafficSpaceUsageValueIterator.d.h"






const AuxiliaryTrafficSpaceUsageValue* ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_next(AuxiliaryTrafficSpaceUsageValueIterator* self);

void ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_destroy(AuxiliaryTrafficSpaceUsageValueIterator* self);





#endif // AuxiliaryTrafficSpaceUsageValueIterator_H
