#ifndef RelationTypeValue_H
#define RelationTypeValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "RelationTypeValue.d.h"






const Code* ecitygml_RelationTypeValue_code(const RelationTypeValue* self);

DiplomatStringView ecitygml_RelationTypeValue_value(const RelationTypeValue* self);

void ecitygml_RelationTypeValue_destroy(RelationTypeValue* self);





#endif // RelationTypeValue_H
