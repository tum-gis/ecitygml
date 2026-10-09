#ifndef BridgeClassValue_H
#define BridgeClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BridgeClassValue.d.h"






const Code* ecitygml_BridgeClassValue_code(const BridgeClassValue* self);

DiplomatStringView ecitygml_BridgeClassValue_value(const BridgeClassValue* self);

void ecitygml_BridgeClassValue_destroy(BridgeClassValue* self);





#endif // BridgeClassValue_H
