#ifndef Intersection_H
#define Intersection_H

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
#include "IntersectionClassValue.d.h"
#include "MarkingPropertyIterator.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "OccupancyIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"
#include "TrafficDirectionValue.d.h"
#include "TrafficSpacePropertyIterator.d.h"

#include "Intersection.d.h"






const Id* ecitygml_Intersection_id(const Intersection* self);

CodeIterator* ecitygml_Intersection_names(const Intersection* self);

const BoundingShape* ecitygml_Intersection_bounded_by(const Intersection* self);

const Id* ecitygml_Intersection_feature_id(const Intersection* self);

const DateTime* ecitygml_Intersection_creation_date(const Intersection* self);

const DateTime* ecitygml_Intersection_termination_date(const Intersection* self);

const DateTime* ecitygml_Intersection_valid_from(const Intersection* self);

const DateTime* ecitygml_Intersection_valid_to(const Intersection* self);

typedef struct ecitygml_Intersection_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Intersection_relative_to_terrain_result;
ecitygml_Intersection_relative_to_terrain_result ecitygml_Intersection_relative_to_terrain(const Intersection* self);

typedef struct ecitygml_Intersection_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Intersection_relative_to_water_result;
ecitygml_Intersection_relative_to_water_result ecitygml_Intersection_relative_to_water(const Intersection* self);

ExternalReferenceIterator* ecitygml_Intersection_external_references(const Intersection* self);

GenericAttributeKindIterator* ecitygml_Intersection_generic_attributes(const Intersection* self);

CityObjectRelationPropertyIterator* ecitygml_Intersection_related_to(const Intersection* self);

typedef struct ecitygml_Intersection_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Intersection_space_type_result;
ecitygml_Intersection_space_type_result ecitygml_Intersection_space_type(const Intersection* self);

const SolidProperty* ecitygml_Intersection_lod1_solid(const Intersection* self);

const SolidProperty* ecitygml_Intersection_lod2_solid(const Intersection* self);

const SolidProperty* ecitygml_Intersection_lod3_solid(const Intersection* self);

const MultiSurfaceProperty* ecitygml_Intersection_lod0_multi_surface(const Intersection* self);

const MultiSurfaceProperty* ecitygml_Intersection_lod2_multi_surface(const Intersection* self);

const MultiSurfaceProperty* ecitygml_Intersection_lod3_multi_surface(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod0_multi_curve(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod2_multi_curve(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod3_multi_curve(const Intersection* self);

const PointProperty* ecitygml_Intersection_lod0_point(const Intersection* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Intersection_boundaries(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod1_terrain_intersection_curve(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod2_terrain_intersection_curve(const Intersection* self);

const MultiCurveProperty* ecitygml_Intersection_lod3_terrain_intersection_curve(const Intersection* self);

typedef struct ecitygml_Intersection_traffic_direction_result {union {TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Intersection_traffic_direction_result;
ecitygml_Intersection_traffic_direction_result ecitygml_Intersection_traffic_direction(const Intersection* self);

OccupancyIterator* ecitygml_Intersection_occupancies(const Intersection* self);

TrafficSpacePropertyIterator* ecitygml_Intersection_traffic_spaces(const Intersection* self);

AuxiliaryTrafficSpacePropertyIterator* ecitygml_Intersection_auxiliary_traffic_spaces(const Intersection* self);

MarkingPropertyIterator* ecitygml_Intersection_markings(const Intersection* self);

HolePropertyIterator* ecitygml_Intersection_holes(const Intersection* self);

const Intersection* ecitygml_Intersection_try_from(const AbstractFeatureKindRef* feature);

const IntersectionClassValue* ecitygml_Intersection_class(const Intersection* self);

void ecitygml_Intersection_destroy(Intersection* self);





#endif // Intersection_H
