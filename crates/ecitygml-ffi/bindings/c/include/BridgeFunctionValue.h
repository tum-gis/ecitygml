#ifndef BridgeFunctionValue_H
#define BridgeFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BridgeFunctionValue.d.h"






const Code* ecitygml_BridgeFunctionValue_code(const BridgeFunctionValue* self);

DiplomatStringView ecitygml_BridgeFunctionValue_value(const BridgeFunctionValue* self);

void ecitygml_BridgeFunctionValue_destroy(BridgeFunctionValue* self);





#endif // BridgeFunctionValue_H
