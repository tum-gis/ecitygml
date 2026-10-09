#ifndef TunnelFunctionValue_H
#define TunnelFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TunnelFunctionValue.d.h"






const Code* ecitygml_TunnelFunctionValue_code(const TunnelFunctionValue* self);

DiplomatStringView ecitygml_TunnelFunctionValue_value(const TunnelFunctionValue* self);

void ecitygml_TunnelFunctionValue_destroy(TunnelFunctionValue* self);





#endif // TunnelFunctionValue_H
