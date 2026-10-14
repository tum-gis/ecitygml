#ifndef AbstractCityObjectKindRef_H
#define AbstractCityObjectKindRef_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectKind.d.h"
#include "FeatureType.d.h"

#include "AbstractCityObjectKindRef.d.h"






AbstractCityObjectKindRef* ecitygml_AbstractCityObjectKindRef_from_city_object(const AbstractCityObjectKind* city_object);

FeatureType ecitygml_AbstractCityObjectKindRef_feature_type(const AbstractCityObjectKindRef* self);

void ecitygml_AbstractCityObjectKindRef_destroy(AbstractCityObjectKindRef* self);





#endif // AbstractCityObjectKindRef_H
