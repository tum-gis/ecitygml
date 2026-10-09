#ifndef AuxiliaryTrafficAreaUsageValueIterator_H
#define AuxiliaryTrafficAreaUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficAreaUsageValue.d.h"

#include "AuxiliaryTrafficAreaUsageValueIterator.d.h"






const AuxiliaryTrafficAreaUsageValue* ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next(AuxiliaryTrafficAreaUsageValueIterator* self);

void ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy(AuxiliaryTrafficAreaUsageValueIterator* self);





#endif // AuxiliaryTrafficAreaUsageValueIterator_H
