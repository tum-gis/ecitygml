#ifndef AbstractBuildingSubdivisionPropertyIterator_H
#define AbstractBuildingSubdivisionPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractBuildingSubdivisionProperty.d.h"

#include "AbstractBuildingSubdivisionPropertyIterator.d.h"






const AbstractBuildingSubdivisionProperty* ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(AbstractBuildingSubdivisionPropertyIterator* self);

void ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(AbstractBuildingSubdivisionPropertyIterator* self);





#endif // AbstractBuildingSubdivisionPropertyIterator_H
