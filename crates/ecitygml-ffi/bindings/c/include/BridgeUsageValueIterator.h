#ifndef BridgeUsageValueIterator_H
#define BridgeUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BridgeUsageValue.d.h"

#include "BridgeUsageValueIterator.d.h"






const BridgeUsageValue* ecitygml_BridgeUsageValueIterator_next(BridgeUsageValueIterator* self);

void ecitygml_BridgeUsageValueIterator_destroy(BridgeUsageValueIterator* self);





#endif // BridgeUsageValueIterator_H
