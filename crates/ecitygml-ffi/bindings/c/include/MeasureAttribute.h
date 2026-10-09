#ifndef MeasureAttribute_H
#define MeasureAttribute_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "GenericAttributeKind.d.h"
#include "Measure.d.h"

#include "MeasureAttribute.d.h"






const MeasureAttribute* ecitygml_MeasureAttribute_try_from(const GenericAttributeKind* attribute);

DiplomatStringView ecitygml_MeasureAttribute_name(const MeasureAttribute* self);

const Measure* ecitygml_MeasureAttribute_value(const MeasureAttribute* self);

void ecitygml_MeasureAttribute_destroy(MeasureAttribute* self);





#endif // MeasureAttribute_H
