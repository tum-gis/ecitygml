#ifndef PlantCoverClassValue_H
#define PlantCoverClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "PlantCoverClassValue.d.h"






const Code* ecitygml_PlantCoverClassValue_code(const PlantCoverClassValue* self);

DiplomatStringView ecitygml_PlantCoverClassValue_value(const PlantCoverClassValue* self);

void ecitygml_PlantCoverClassValue_destroy(PlantCoverClassValue* self);





#endif // PlantCoverClassValue_H
