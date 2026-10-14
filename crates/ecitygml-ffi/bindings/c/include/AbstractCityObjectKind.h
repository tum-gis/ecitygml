#ifndef AbstractCityObjectKind_H
#define AbstractCityObjectKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "FeatureType.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"

#include "AbstractCityObjectKind.d.h"






const Id* ecitygml_AbstractCityObjectKind_id(const AbstractCityObjectKind* self);

CodeIterator* ecitygml_AbstractCityObjectKind_names(const AbstractCityObjectKind* self);

const BoundingShape* ecitygml_AbstractCityObjectKind_bounded_by(const AbstractCityObjectKind* self);

const Id* ecitygml_AbstractCityObjectKind_feature_id(const AbstractCityObjectKind* self);

const DateTime* ecitygml_AbstractCityObjectKind_creation_date(const AbstractCityObjectKind* self);

const DateTime* ecitygml_AbstractCityObjectKind_termination_date(const AbstractCityObjectKind* self);

const DateTime* ecitygml_AbstractCityObjectKind_valid_from(const AbstractCityObjectKind* self);

const DateTime* ecitygml_AbstractCityObjectKind_valid_to(const AbstractCityObjectKind* self);

typedef struct ecitygml_AbstractCityObjectKind_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractCityObjectKind_relative_to_terrain_result;
ecitygml_AbstractCityObjectKind_relative_to_terrain_result ecitygml_AbstractCityObjectKind_relative_to_terrain(const AbstractCityObjectKind* self);

typedef struct ecitygml_AbstractCityObjectKind_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractCityObjectKind_relative_to_water_result;
ecitygml_AbstractCityObjectKind_relative_to_water_result ecitygml_AbstractCityObjectKind_relative_to_water(const AbstractCityObjectKind* self);

ExternalReferenceIterator* ecitygml_AbstractCityObjectKind_external_references(const AbstractCityObjectKind* self);

GenericAttributeKindIterator* ecitygml_AbstractCityObjectKind_generic_attributes(const AbstractCityObjectKind* self);

CityObjectRelationPropertyIterator* ecitygml_AbstractCityObjectKind_related_to(const AbstractCityObjectKind* self);

FeatureType ecitygml_AbstractCityObjectKind_feature_type(const AbstractCityObjectKind* self);

void ecitygml_AbstractCityObjectKind_destroy(AbstractCityObjectKind* self);





#endif // AbstractCityObjectKind_H
