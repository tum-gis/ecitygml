#ifndef AbstractSpaceBoundaryKind_H
#define AbstractSpaceBoundaryKind_H

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

#include "AbstractSpaceBoundaryKind.d.h"






const Id* ecitygml_AbstractSpaceBoundaryKind_id(const AbstractSpaceBoundaryKind* self);

CodeIterator* ecitygml_AbstractSpaceBoundaryKind_names(const AbstractSpaceBoundaryKind* self);

const BoundingShape* ecitygml_AbstractSpaceBoundaryKind_bounded_by(const AbstractSpaceBoundaryKind* self);

const Id* ecitygml_AbstractSpaceBoundaryKind_feature_id(const AbstractSpaceBoundaryKind* self);

const DateTime* ecitygml_AbstractSpaceBoundaryKind_creation_date(const AbstractSpaceBoundaryKind* self);

const DateTime* ecitygml_AbstractSpaceBoundaryKind_termination_date(const AbstractSpaceBoundaryKind* self);

const DateTime* ecitygml_AbstractSpaceBoundaryKind_valid_from(const AbstractSpaceBoundaryKind* self);

const DateTime* ecitygml_AbstractSpaceBoundaryKind_valid_to(const AbstractSpaceBoundaryKind* self);

typedef struct ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result;
ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain(const AbstractSpaceBoundaryKind* self);

typedef struct ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result;
ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result ecitygml_AbstractSpaceBoundaryKind_relative_to_water(const AbstractSpaceBoundaryKind* self);

ExternalReferenceIterator* ecitygml_AbstractSpaceBoundaryKind_external_references(const AbstractSpaceBoundaryKind* self);

GenericAttributeKindIterator* ecitygml_AbstractSpaceBoundaryKind_generic_attributes(const AbstractSpaceBoundaryKind* self);

CityObjectRelationPropertyIterator* ecitygml_AbstractSpaceBoundaryKind_related_to(const AbstractSpaceBoundaryKind* self);

FeatureType ecitygml_AbstractSpaceBoundaryKind_feature_type(const AbstractSpaceBoundaryKind* self);

void ecitygml_AbstractSpaceBoundaryKind_destroy(AbstractSpaceBoundaryKind* self);





#endif // AbstractSpaceBoundaryKind_H
