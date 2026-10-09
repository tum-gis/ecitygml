#ifndef TinRelief_H
#define TinRelief_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "LevelOfDetail.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "TinProperty.d.h"

#include "TinRelief.d.h"






const Id* ecitygml_TinRelief_id(const TinRelief* self);

CodeIterator* ecitygml_TinRelief_names(const TinRelief* self);

const BoundingShape* ecitygml_TinRelief_bounded_by(const TinRelief* self);

const Id* ecitygml_TinRelief_feature_id(const TinRelief* self);

const DateTime* ecitygml_TinRelief_creation_date(const TinRelief* self);

const DateTime* ecitygml_TinRelief_termination_date(const TinRelief* self);

const DateTime* ecitygml_TinRelief_valid_from(const TinRelief* self);

const DateTime* ecitygml_TinRelief_valid_to(const TinRelief* self);

typedef struct ecitygml_TinRelief_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_TinRelief_relative_to_terrain_result;
ecitygml_TinRelief_relative_to_terrain_result ecitygml_TinRelief_relative_to_terrain(const TinRelief* self);

typedef struct ecitygml_TinRelief_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_TinRelief_relative_to_water_result;
ecitygml_TinRelief_relative_to_water_result ecitygml_TinRelief_relative_to_water(const TinRelief* self);

ExternalReferenceIterator* ecitygml_TinRelief_external_references(const TinRelief* self);

GenericAttributeKindIterator* ecitygml_TinRelief_generic_attributes(const TinRelief* self);

CityObjectRelationPropertyIterator* ecitygml_TinRelief_related_to(const TinRelief* self);

LevelOfDetail ecitygml_TinRelief_lod(const TinRelief* self);

const TinRelief* ecitygml_TinRelief_try_from(const AbstractFeatureKindRef* feature);

const TinProperty* ecitygml_TinRelief_tin(const TinRelief* self);

void ecitygml_TinRelief_destroy(TinRelief* self);





#endif // TinRelief_H
