#ifndef AbstractReliefComponentKind_H
#define AbstractReliefComponentKind_H

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
#include "LevelOfDetail.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"

#include "AbstractReliefComponentKind.d.h"






const Id* ecitygml_AbstractReliefComponentKind_id(const AbstractReliefComponentKind* self);

CodeIterator* ecitygml_AbstractReliefComponentKind_names(const AbstractReliefComponentKind* self);

const BoundingShape* ecitygml_AbstractReliefComponentKind_bounded_by(const AbstractReliefComponentKind* self);

const Id* ecitygml_AbstractReliefComponentKind_feature_id(const AbstractReliefComponentKind* self);

const DateTime* ecitygml_AbstractReliefComponentKind_creation_date(const AbstractReliefComponentKind* self);

const DateTime* ecitygml_AbstractReliefComponentKind_termination_date(const AbstractReliefComponentKind* self);

const DateTime* ecitygml_AbstractReliefComponentKind_valid_from(const AbstractReliefComponentKind* self);

const DateTime* ecitygml_AbstractReliefComponentKind_valid_to(const AbstractReliefComponentKind* self);

typedef struct ecitygml_AbstractReliefComponentKind_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractReliefComponentKind_relative_to_terrain_result;
ecitygml_AbstractReliefComponentKind_relative_to_terrain_result ecitygml_AbstractReliefComponentKind_relative_to_terrain(const AbstractReliefComponentKind* self);

typedef struct ecitygml_AbstractReliefComponentKind_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractReliefComponentKind_relative_to_water_result;
ecitygml_AbstractReliefComponentKind_relative_to_water_result ecitygml_AbstractReliefComponentKind_relative_to_water(const AbstractReliefComponentKind* self);

ExternalReferenceIterator* ecitygml_AbstractReliefComponentKind_external_references(const AbstractReliefComponentKind* self);

GenericAttributeKindIterator* ecitygml_AbstractReliefComponentKind_generic_attributes(const AbstractReliefComponentKind* self);

CityObjectRelationPropertyIterator* ecitygml_AbstractReliefComponentKind_related_to(const AbstractReliefComponentKind* self);

LevelOfDetail ecitygml_AbstractReliefComponentKind_lod(const AbstractReliefComponentKind* self);

FeatureType ecitygml_AbstractReliefComponentKind_feature_type(const AbstractReliefComponentKind* self);

void ecitygml_AbstractReliefComponentKind_destroy(AbstractReliefComponentKind* self);





#endif // AbstractReliefComponentKind_H
