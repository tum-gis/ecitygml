#ifndef TunnelUsageValueIterator_H
#define TunnelUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TunnelUsageValue.d.h"

#include "TunnelUsageValueIterator.d.h"






const TunnelUsageValue* ecitygml_TunnelUsageValueIterator_next(TunnelUsageValueIterator* self);

void ecitygml_TunnelUsageValueIterator_destroy(TunnelUsageValueIterator* self);





#endif // TunnelUsageValueIterator_H
