#ifndef SpeciesValue_H
#define SpeciesValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "SpeciesValue.d.h"






const Code* ecitygml_SpeciesValue_code(const SpeciesValue* self);

DiplomatStringView ecitygml_SpeciesValue_value(const SpeciesValue* self);

void ecitygml_SpeciesValue_destroy(SpeciesValue* self);





#endif // SpeciesValue_H
