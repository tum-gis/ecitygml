#ifndef TunnelUsageValue_H
#define TunnelUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TunnelUsageValue.d.h"






const Code* ecitygml_TunnelUsageValue_code(const TunnelUsageValue* self);

DiplomatStringView ecitygml_TunnelUsageValue_value(const TunnelUsageValue* self);

void ecitygml_TunnelUsageValue_destroy(TunnelUsageValue* self);





#endif // TunnelUsageValue_H
