#ifndef AuxiliaryTrafficSpaceFunctionValue_H
#define AuxiliaryTrafficSpaceFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "AuxiliaryTrafficSpaceFunctionValue.d.h"






const Code* ecitygml_AuxiliaryTrafficSpaceFunctionValue_code(const AuxiliaryTrafficSpaceFunctionValue* self);

DiplomatStringView ecitygml_AuxiliaryTrafficSpaceFunctionValue_value(const AuxiliaryTrafficSpaceFunctionValue* self);

void ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy(AuxiliaryTrafficSpaceFunctionValue* self);





#endif // AuxiliaryTrafficSpaceFunctionValue_H
