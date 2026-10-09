#ifndef CityObjectRelationProperty_H
#define CityObjectRelationProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityObjectRelation.d.h"
#include "HRef.d.h"

#include "CityObjectRelationProperty.d.h"






const CityObjectRelation* ecitygml_CityObjectRelationProperty_object(const CityObjectRelationProperty* self);

const HRef* ecitygml_CityObjectRelationProperty_href(const CityObjectRelationProperty* self);

void ecitygml_CityObjectRelationProperty_destroy(CityObjectRelationProperty* self);





#endif // CityObjectRelationProperty_H
