#ifndef SurfaceMaterialValue_H
#define SurfaceMaterialValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "SurfaceMaterialValue.d.h"






const Code* ecitygml_SurfaceMaterialValue_code(const SurfaceMaterialValue* self);

DiplomatStringView ecitygml_SurfaceMaterialValue_value(const SurfaceMaterialValue* self);

void ecitygml_SurfaceMaterialValue_destroy(SurfaceMaterialValue* self);





#endif // SurfaceMaterialValue_H
