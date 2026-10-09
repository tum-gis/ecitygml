#ifndef ElevationReferenceValue_H
#define ElevationReferenceValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "ElevationReferenceValue.d.h"






const Code* ecitygml_ElevationReferenceValue_code(const ElevationReferenceValue* self);

DiplomatStringView ecitygml_ElevationReferenceValue_value(const ElevationReferenceValue* self);

void ecitygml_ElevationReferenceValue_destroy(ElevationReferenceValue* self);





#endif // ElevationReferenceValue_H
