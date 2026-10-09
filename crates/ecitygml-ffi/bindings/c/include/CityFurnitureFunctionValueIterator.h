#ifndef CityFurnitureFunctionValueIterator_H
#define CityFurnitureFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityFurnitureFunctionValue.d.h"

#include "CityFurnitureFunctionValueIterator.d.h"






const CityFurnitureFunctionValue* ecitygml_CityFurnitureFunctionValueIterator_next(CityFurnitureFunctionValueIterator* self);

void ecitygml_CityFurnitureFunctionValueIterator_destroy(CityFurnitureFunctionValueIterator* self);





#endif // CityFurnitureFunctionValueIterator_H
