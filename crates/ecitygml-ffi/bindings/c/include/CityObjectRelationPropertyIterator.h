#ifndef CityObjectRelationPropertyIterator_H
#define CityObjectRelationPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityObjectRelationProperty.d.h"

#include "CityObjectRelationPropertyIterator.d.h"






const CityObjectRelationProperty* ecitygml_CityObjectRelationPropertyIterator_next(CityObjectRelationPropertyIterator* self);

void ecitygml_CityObjectRelationPropertyIterator_destroy(CityObjectRelationPropertyIterator* self);





#endif // CityObjectRelationPropertyIterator_H
