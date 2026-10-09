#ifndef ReliefFeature_H
#define ReliefFeature_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractReliefComponentPropertyIterator.d.h"
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

#include "ReliefFeature.d.h"






const Id* ecitygml_ReliefFeature_id(const ReliefFeature* self);

CodeIterator* ecitygml_ReliefFeature_names(const ReliefFeature* self);

const BoundingShape* ecitygml_ReliefFeature_bounded_by(const ReliefFeature* self);

const Id* ecitygml_ReliefFeature_feature_id(const ReliefFeature* self);

const DateTime* ecitygml_ReliefFeature_creation_date(const ReliefFeature* self);

const DateTime* ecitygml_ReliefFeature_termination_date(const ReliefFeature* self);

const DateTime* ecitygml_ReliefFeature_valid_from(const ReliefFeature* self);

const DateTime* ecitygml_ReliefFeature_valid_to(const ReliefFeature* self);

typedef struct ecitygml_ReliefFeature_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_ReliefFeature_relative_to_terrain_result;
ecitygml_ReliefFeature_relative_to_terrain_result ecitygml_ReliefFeature_relative_to_terrain(const ReliefFeature* self);

typedef struct ecitygml_ReliefFeature_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_ReliefFeature_relative_to_water_result;
ecitygml_ReliefFeature_relative_to_water_result ecitygml_ReliefFeature_relative_to_water(const ReliefFeature* self);

ExternalReferenceIterator* ecitygml_ReliefFeature_external_references(const ReliefFeature* self);

GenericAttributeKindIterator* ecitygml_ReliefFeature_generic_attributes(const ReliefFeature* self);

CityObjectRelationPropertyIterator* ecitygml_ReliefFeature_related_to(const ReliefFeature* self);

const ReliefFeature* ecitygml_ReliefFeature_try_from(const AbstractFeatureKindRef* feature);

LevelOfDetail ecitygml_ReliefFeature_lod(const ReliefFeature* self);

AbstractReliefComponentPropertyIterator* ecitygml_ReliefFeature_relief_components(const ReliefFeature* self);

void ecitygml_ReliefFeature_destroy(ReliefFeature* self);





#endif // ReliefFeature_H
