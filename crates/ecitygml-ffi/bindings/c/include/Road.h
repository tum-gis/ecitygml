#ifndef Road_H
#define Road_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "AuxiliaryTrafficSpacePropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "HolePropertyIterator.d.h"
#include "Id.d.h"
#include "IntersectionPropertyIterator.d.h"
#include "MarkingPropertyIterator.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "OccupancyIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "RoadClassValue.d.h"
#include "RoadFunctionValueIterator.d.h"
#include "RoadUsageValueIterator.d.h"
#include "SectionPropertyIterator.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"
#include "TrafficDirectionValue.d.h"
#include "TrafficSpacePropertyIterator.d.h"

#include "Road.d.h"






const Id* ecitygml_Road_id(const Road* self);

CodeIterator* ecitygml_Road_names(const Road* self);

const BoundingShape* ecitygml_Road_bounded_by(const Road* self);

const Id* ecitygml_Road_feature_id(const Road* self);

const DateTime* ecitygml_Road_creation_date(const Road* self);

const DateTime* ecitygml_Road_termination_date(const Road* self);

const DateTime* ecitygml_Road_valid_from(const Road* self);

const DateTime* ecitygml_Road_valid_to(const Road* self);

typedef struct ecitygml_Road_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Road_relative_to_terrain_result;
ecitygml_Road_relative_to_terrain_result ecitygml_Road_relative_to_terrain(const Road* self);

typedef struct ecitygml_Road_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Road_relative_to_water_result;
ecitygml_Road_relative_to_water_result ecitygml_Road_relative_to_water(const Road* self);

ExternalReferenceIterator* ecitygml_Road_external_references(const Road* self);

GenericAttributeKindIterator* ecitygml_Road_generic_attributes(const Road* self);

CityObjectRelationPropertyIterator* ecitygml_Road_related_to(const Road* self);

typedef struct ecitygml_Road_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Road_space_type_result;
ecitygml_Road_space_type_result ecitygml_Road_space_type(const Road* self);

const SolidProperty* ecitygml_Road_lod1_solid(const Road* self);

const SolidProperty* ecitygml_Road_lod2_solid(const Road* self);

const SolidProperty* ecitygml_Road_lod3_solid(const Road* self);

const MultiSurfaceProperty* ecitygml_Road_lod0_multi_surface(const Road* self);

const MultiSurfaceProperty* ecitygml_Road_lod2_multi_surface(const Road* self);

const MultiSurfaceProperty* ecitygml_Road_lod3_multi_surface(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod0_multi_curve(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod2_multi_curve(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod3_multi_curve(const Road* self);

const PointProperty* ecitygml_Road_lod0_point(const Road* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Road_boundaries(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod1_terrain_intersection_curve(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod2_terrain_intersection_curve(const Road* self);

const MultiCurveProperty* ecitygml_Road_lod3_terrain_intersection_curve(const Road* self);

typedef struct ecitygml_Road_traffic_direction_result {union {TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Road_traffic_direction_result;
ecitygml_Road_traffic_direction_result ecitygml_Road_traffic_direction(const Road* self);

OccupancyIterator* ecitygml_Road_occupancies(const Road* self);

TrafficSpacePropertyIterator* ecitygml_Road_traffic_spaces(const Road* self);

AuxiliaryTrafficSpacePropertyIterator* ecitygml_Road_auxiliary_traffic_spaces(const Road* self);

MarkingPropertyIterator* ecitygml_Road_markings(const Road* self);

HolePropertyIterator* ecitygml_Road_holes(const Road* self);

const Road* ecitygml_Road_try_from(const AbstractFeatureKindRef* feature);

const RoadClassValue* ecitygml_Road_class(const Road* self);

RoadFunctionValueIterator* ecitygml_Road_functions(const Road* self);

RoadUsageValueIterator* ecitygml_Road_usages(const Road* self);

SectionPropertyIterator* ecitygml_Road_sections(const Road* self);

IntersectionPropertyIterator* ecitygml_Road_intersections(const Road* self);

void ecitygml_Road_destroy(Road* self);





#endif // Road_H
