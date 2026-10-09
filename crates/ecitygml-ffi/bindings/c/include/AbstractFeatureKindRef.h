#ifndef AbstractFeatureKindRef_H
#define AbstractFeatureKindRef_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectKindRef.d.h"
#include "AbstractSpaceBoundaryKind.d.h"
#include "FeatureType.d.h"

#include "AbstractFeatureKindRef.d.h"






AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRef_from_space_boundary(const AbstractSpaceBoundaryKind* boundary);

AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRef_from_city_object(const AbstractCityObjectKindRef* city_object);

FeatureType ecitygml_AbstractFeatureKindRef_feature_type(const AbstractFeatureKindRef* self);

void ecitygml_AbstractFeatureKindRef_destroy(AbstractFeatureKindRef* self);





#endif // AbstractFeatureKindRef_H
