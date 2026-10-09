#ifndef Height_H
#define Height_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "ElevationReferenceValue.d.h"
#include "HeightStatusValue.d.h"
#include "Length.d.h"

#include "Height.d.h"






const ElevationReferenceValue* ecitygml_Height_high_reference(const Height* self);

const ElevationReferenceValue* ecitygml_Height_low_reference(const Height* self);

HeightStatusValue ecitygml_Height_status(const Height* self);

const Length* ecitygml_Height_length(const Height* self);

void ecitygml_Height_destroy(Height* self);





#endif // Height_H
