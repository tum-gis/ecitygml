#ifndef AbstractBuildingSubdivisionProperty_H
#define AbstractBuildingSubdivisionProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractBuildingSubdivisionKind.d.h"
#include "HRef.d.h"

#include "AbstractBuildingSubdivisionProperty.d.h"






const AbstractBuildingSubdivisionKind* ecitygml_AbstractBuildingSubdivisionProperty_object(const AbstractBuildingSubdivisionProperty* self);

const HRef* ecitygml_AbstractBuildingSubdivisionProperty_href(const AbstractBuildingSubdivisionProperty* self);

void ecitygml_AbstractBuildingSubdivisionProperty_destroy(AbstractBuildingSubdivisionProperty* self);





#endif // AbstractBuildingSubdivisionProperty_H
