#ifndef IntersectionClassValue_H
#define IntersectionClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "IntersectionClassValue.d.h"






const Code* ecitygml_IntersectionClassValue_code(const IntersectionClassValue* self);

DiplomatStringView ecitygml_IntersectionClassValue_value(const IntersectionClassValue* self);

void ecitygml_IntersectionClassValue_destroy(IntersectionClassValue* self);





#endif // IntersectionClassValue_H
