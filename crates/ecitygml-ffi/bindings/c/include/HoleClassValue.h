#ifndef HoleClassValue_H
#define HoleClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "HoleClassValue.d.h"






const Code* ecitygml_HoleClassValue_code(const HoleClassValue* self);

DiplomatStringView ecitygml_HoleClassValue_value(const HoleClassValue* self);

void ecitygml_HoleClassValue_destroy(HoleClassValue* self);





#endif // HoleClassValue_H
