#ifndef AbstractBuildingSubdivisionKind_H
#define AbstractBuildingSubdivisionKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "BuildingSubdivisionClassValue.d.h"
#include "BuildingSubdivisionFunctionValueIterator.d.h"
#include "BuildingSubdivisionUsageValueIterator.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "FeatureType.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "AbstractBuildingSubdivisionKind.d.h"






const Id* ecitygml_AbstractBuildingSubdivisionKind_id(const AbstractBuildingSubdivisionKind* self);

CodeIterator* ecitygml_AbstractBuildingSubdivisionKind_names(const AbstractBuildingSubdivisionKind* self);

const BoundingShape* ecitygml_AbstractBuildingSubdivisionKind_bounded_by(const AbstractBuildingSubdivisionKind* self);

const Id* ecitygml_AbstractBuildingSubdivisionKind_feature_id(const AbstractBuildingSubdivisionKind* self);

const DateTime* ecitygml_AbstractBuildingSubdivisionKind_creation_date(const AbstractBuildingSubdivisionKind* self);

const DateTime* ecitygml_AbstractBuildingSubdivisionKind_termination_date(const AbstractBuildingSubdivisionKind* self);

const DateTime* ecitygml_AbstractBuildingSubdivisionKind_valid_from(const AbstractBuildingSubdivisionKind* self);

const DateTime* ecitygml_AbstractBuildingSubdivisionKind_valid_to(const AbstractBuildingSubdivisionKind* self);

typedef struct ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result;
ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain(const AbstractBuildingSubdivisionKind* self);

typedef struct ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result;
ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result ecitygml_AbstractBuildingSubdivisionKind_relative_to_water(const AbstractBuildingSubdivisionKind* self);

ExternalReferenceIterator* ecitygml_AbstractBuildingSubdivisionKind_external_references(const AbstractBuildingSubdivisionKind* self);

GenericAttributeKindIterator* ecitygml_AbstractBuildingSubdivisionKind_generic_attributes(const AbstractBuildingSubdivisionKind* self);

CityObjectRelationPropertyIterator* ecitygml_AbstractBuildingSubdivisionKind_related_to(const AbstractBuildingSubdivisionKind* self);

typedef struct ecitygml_AbstractBuildingSubdivisionKind_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_space_type_result;
ecitygml_AbstractBuildingSubdivisionKind_space_type_result ecitygml_AbstractBuildingSubdivisionKind_space_type(const AbstractBuildingSubdivisionKind* self);

const SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod1_solid(const AbstractBuildingSubdivisionKind* self);

const SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_solid(const AbstractBuildingSubdivisionKind* self);

const SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_solid(const AbstractBuildingSubdivisionKind* self);

const MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_surface(const AbstractBuildingSubdivisionKind* self);

const MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_surface(const AbstractBuildingSubdivisionKind* self);

const MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_surface(const AbstractBuildingSubdivisionKind* self);

const MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_curve(const AbstractBuildingSubdivisionKind* self);

const MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_curve(const AbstractBuildingSubdivisionKind* self);

const MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_curve(const AbstractBuildingSubdivisionKind* self);

const PointProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_point(const AbstractBuildingSubdivisionKind* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_AbstractBuildingSubdivisionKind_boundaries(const AbstractBuildingSubdivisionKind* self);

const BuildingSubdivisionClassValue* ecitygml_AbstractBuildingSubdivisionKind_class(const AbstractBuildingSubdivisionKind* self);

BuildingSubdivisionFunctionValueIterator* ecitygml_AbstractBuildingSubdivisionKind_functions(const AbstractBuildingSubdivisionKind* self);

BuildingSubdivisionUsageValueIterator* ecitygml_AbstractBuildingSubdivisionKind_usages(const AbstractBuildingSubdivisionKind* self);

FeatureType ecitygml_AbstractBuildingSubdivisionKind_feature_type(const AbstractBuildingSubdivisionKind* self);

void ecitygml_AbstractBuildingSubdivisionKind_destroy(AbstractBuildingSubdivisionKind* self);





#endif // AbstractBuildingSubdivisionKind_H
