#ifndef TrafficSpace_H
#define TrafficSpace_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "GranularityValue.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "OccupancyIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"
#include "TrafficDirectionValue.d.h"
#include "TrafficSpaceClassValue.d.h"
#include "TrafficSpaceFunctionValueIterator.d.h"
#include "TrafficSpaceUsageValueIterator.d.h"

#include "TrafficSpace.d.h"






const Id* ecitygml_TrafficSpace_id(const TrafficSpace* self);

CodeIterator* ecitygml_TrafficSpace_names(const TrafficSpace* self);

const BoundingShape* ecitygml_TrafficSpace_bounded_by(const TrafficSpace* self);

const Id* ecitygml_TrafficSpace_feature_id(const TrafficSpace* self);

const DateTime* ecitygml_TrafficSpace_creation_date(const TrafficSpace* self);

const DateTime* ecitygml_TrafficSpace_termination_date(const TrafficSpace* self);

const DateTime* ecitygml_TrafficSpace_valid_from(const TrafficSpace* self);

const DateTime* ecitygml_TrafficSpace_valid_to(const TrafficSpace* self);

typedef struct ecitygml_TrafficSpace_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_TrafficSpace_relative_to_terrain_result;
ecitygml_TrafficSpace_relative_to_terrain_result ecitygml_TrafficSpace_relative_to_terrain(const TrafficSpace* self);

typedef struct ecitygml_TrafficSpace_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_TrafficSpace_relative_to_water_result;
ecitygml_TrafficSpace_relative_to_water_result ecitygml_TrafficSpace_relative_to_water(const TrafficSpace* self);

ExternalReferenceIterator* ecitygml_TrafficSpace_external_references(const TrafficSpace* self);

GenericAttributeKindIterator* ecitygml_TrafficSpace_generic_attributes(const TrafficSpace* self);

CityObjectRelationPropertyIterator* ecitygml_TrafficSpace_related_to(const TrafficSpace* self);

typedef struct ecitygml_TrafficSpace_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_TrafficSpace_space_type_result;
ecitygml_TrafficSpace_space_type_result ecitygml_TrafficSpace_space_type(const TrafficSpace* self);

const SolidProperty* ecitygml_TrafficSpace_lod1_solid(const TrafficSpace* self);

const SolidProperty* ecitygml_TrafficSpace_lod2_solid(const TrafficSpace* self);

const SolidProperty* ecitygml_TrafficSpace_lod3_solid(const TrafficSpace* self);

const MultiSurfaceProperty* ecitygml_TrafficSpace_lod0_multi_surface(const TrafficSpace* self);

const MultiSurfaceProperty* ecitygml_TrafficSpace_lod2_multi_surface(const TrafficSpace* self);

const MultiSurfaceProperty* ecitygml_TrafficSpace_lod3_multi_surface(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod0_multi_curve(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod2_multi_curve(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod3_multi_curve(const TrafficSpace* self);

const PointProperty* ecitygml_TrafficSpace_lod0_point(const TrafficSpace* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_TrafficSpace_boundaries(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod1_terrain_intersection_curve(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod2_terrain_intersection_curve(const TrafficSpace* self);

const MultiCurveProperty* ecitygml_TrafficSpace_lod3_terrain_intersection_curve(const TrafficSpace* self);

const TrafficSpace* ecitygml_TrafficSpace_try_from(const AbstractFeatureKindRef* feature);

const TrafficSpaceClassValue* ecitygml_TrafficSpace_class(const TrafficSpace* self);

TrafficSpaceFunctionValueIterator* ecitygml_TrafficSpace_functions(const TrafficSpace* self);

TrafficSpaceUsageValueIterator* ecitygml_TrafficSpace_usages(const TrafficSpace* self);

GranularityValue ecitygml_TrafficSpace_granularity(const TrafficSpace* self);

typedef struct ecitygml_TrafficSpace_traffic_direction_result {union {TrafficDirectionValue ok; }; bool is_ok;} ecitygml_TrafficSpace_traffic_direction_result;
ecitygml_TrafficSpace_traffic_direction_result ecitygml_TrafficSpace_traffic_direction(const TrafficSpace* self);

OccupancyIterator* ecitygml_TrafficSpace_occupancies(const TrafficSpace* self);

void ecitygml_TrafficSpace_destroy(TrafficSpace* self);





#endif // TrafficSpace_H
