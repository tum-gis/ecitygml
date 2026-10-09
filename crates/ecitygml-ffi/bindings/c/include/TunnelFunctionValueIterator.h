#ifndef TunnelFunctionValueIterator_H
#define TunnelFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TunnelFunctionValue.d.h"

#include "TunnelFunctionValueIterator.d.h"






const TunnelFunctionValue* ecitygml_TunnelFunctionValueIterator_next(TunnelFunctionValueIterator* self);

void ecitygml_TunnelFunctionValueIterator_destroy(TunnelFunctionValueIterator* self);





#endif // TunnelFunctionValueIterator_H
