#ifndef RoofTypeValue_H
#define RoofTypeValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "RoofTypeValue.d.h"






const Code* ecitygml_RoofTypeValue_code(const RoofTypeValue* self);

DiplomatStringView ecitygml_RoofTypeValue_value(const RoofTypeValue* self);

void ecitygml_RoofTypeValue_destroy(RoofTypeValue* self);





#endif // RoofTypeValue_H
