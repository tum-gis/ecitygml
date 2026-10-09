#ifndef SectionClassValue_H
#define SectionClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "SectionClassValue.d.h"






const Code* ecitygml_SectionClassValue_code(const SectionClassValue* self);

DiplomatStringView ecitygml_SectionClassValue_value(const SectionClassValue* self);

void ecitygml_SectionClassValue_destroy(SectionClassValue* self);





#endif // SectionClassValue_H
