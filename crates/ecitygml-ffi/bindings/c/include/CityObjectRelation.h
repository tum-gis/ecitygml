#ifndef CityObjectRelation_H
#define CityObjectRelation_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "GenericAttributeKindIterator.d.h"
#include "Reference.d.h"
#include "RelationTypeValue.d.h"

#include "CityObjectRelation.d.h"






const RelationTypeValue* ecitygml_CityObjectRelation_relation_type(const CityObjectRelation* self);

const Reference* ecitygml_CityObjectRelation_relation_to(const CityObjectRelation* self);

GenericAttributeKindIterator* ecitygml_CityObjectRelation_generic_attributes(const CityObjectRelation* self);

void ecitygml_CityObjectRelation_destroy(CityObjectRelation* self);





#endif // CityObjectRelation_H
