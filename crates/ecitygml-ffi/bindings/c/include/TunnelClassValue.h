#ifndef TunnelClassValue_H
#define TunnelClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TunnelClassValue.d.h"






const Code* ecitygml_TunnelClassValue_code(const TunnelClassValue* self);

DiplomatStringView ecitygml_TunnelClassValue_value(const TunnelClassValue* self);

void ecitygml_TunnelClassValue_destroy(TunnelClassValue* self);





#endif // TunnelClassValue_H
