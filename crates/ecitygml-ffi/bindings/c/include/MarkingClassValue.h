#ifndef MarkingClassValue_H
#define MarkingClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "MarkingClassValue.d.h"






const Code* ecitygml_MarkingClassValue_code(const MarkingClassValue* self);

DiplomatStringView ecitygml_MarkingClassValue_value(const MarkingClassValue* self);

void ecitygml_MarkingClassValue_destroy(MarkingClassValue* self);





#endif // MarkingClassValue_H
