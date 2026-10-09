#ifndef BuildingPartPropertyIterator_H
#define BuildingPartPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingPartProperty.d.h"

#include "BuildingPartPropertyIterator.d.h"






const BuildingPartProperty* ecitygml_BuildingPartPropertyIterator_next(BuildingPartPropertyIterator* self);

void ecitygml_BuildingPartPropertyIterator_destroy(BuildingPartPropertyIterator* self);





#endif // BuildingPartPropertyIterator_H
