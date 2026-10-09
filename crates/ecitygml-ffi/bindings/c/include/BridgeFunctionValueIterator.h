#ifndef BridgeFunctionValueIterator_H
#define BridgeFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BridgeFunctionValue.d.h"

#include "BridgeFunctionValueIterator.d.h"






const BridgeFunctionValue* ecitygml_BridgeFunctionValueIterator_next(BridgeFunctionValueIterator* self);

void ecitygml_BridgeFunctionValueIterator_destroy(BridgeFunctionValueIterator* self);





#endif // BridgeFunctionValueIterator_H
