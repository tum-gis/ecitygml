#ifndef IntervalValue_H
#define IntervalValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "IntervalValue.d.h"






const Code* ecitygml_IntervalValue_code(const IntervalValue* self);

DiplomatStringView ecitygml_IntervalValue_value(const IntervalValue* self);

void ecitygml_IntervalValue_destroy(IntervalValue* self);





#endif // IntervalValue_H
