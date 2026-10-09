#ifndef BridgeUsageValue_H
#define BridgeUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BridgeUsageValue.d.h"






const Code* ecitygml_BridgeUsageValue_code(const BridgeUsageValue* self);

DiplomatStringView ecitygml_BridgeUsageValue_value(const BridgeUsageValue* self);

void ecitygml_BridgeUsageValue_destroy(BridgeUsageValue* self);





#endif // BridgeUsageValue_H
