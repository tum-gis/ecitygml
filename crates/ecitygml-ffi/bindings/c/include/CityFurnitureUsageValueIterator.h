#ifndef CityFurnitureUsageValueIterator_H
#define CityFurnitureUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityFurnitureUsageValue.d.h"

#include "CityFurnitureUsageValueIterator.d.h"






const CityFurnitureUsageValue* ecitygml_CityFurnitureUsageValueIterator_next(CityFurnitureUsageValueIterator* self);

void ecitygml_CityFurnitureUsageValueIterator_destroy(CityFurnitureUsageValueIterator* self);





#endif // CityFurnitureUsageValueIterator_H
