#ifndef BuildingPartProperty_H
#define BuildingPartProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingPart.d.h"
#include "HRef.d.h"

#include "BuildingPartProperty.d.h"






const BuildingPart* ecitygml_BuildingPartProperty_object(const BuildingPartProperty* self);

const HRef* ecitygml_BuildingPartProperty_href(const BuildingPartProperty* self);

void ecitygml_BuildingPartProperty_destroy(BuildingPartProperty* self);





#endif // BuildingPartProperty_H
