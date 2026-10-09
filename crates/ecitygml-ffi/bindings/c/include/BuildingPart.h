#ifndef BuildingPart_H
#define BuildingPart_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractBuildingSubdivisionPropertyIterator.d.h"
#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "BuildingClassValue.d.h"
#include "BuildingFunctionValueIterator.d.h"
#include "BuildingUsageValueIterator.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "Date.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "HeightIterator.d.h"
#include "Id.d.h"
#include "ImplicitGeometryProperty.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "OccupancyIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "RoofTypeValue.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "BuildingPart.d.h"






const Id* ecitygml_BuildingPart_id(const BuildingPart* self);

CodeIterator* ecitygml_BuildingPart_names(const BuildingPart* self);

const BoundingShape* ecitygml_BuildingPart_bounded_by(const BuildingPart* self);

const Id* ecitygml_BuildingPart_feature_id(const BuildingPart* self);

const DateTime* ecitygml_BuildingPart_creation_date(const BuildingPart* self);

const DateTime* ecitygml_BuildingPart_termination_date(const BuildingPart* self);

const DateTime* ecitygml_BuildingPart_valid_from(const BuildingPart* self);

const DateTime* ecitygml_BuildingPart_valid_to(const BuildingPart* self);

typedef struct ecitygml_BuildingPart_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_BuildingPart_relative_to_terrain_result;
ecitygml_BuildingPart_relative_to_terrain_result ecitygml_BuildingPart_relative_to_terrain(const BuildingPart* self);

typedef struct ecitygml_BuildingPart_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_BuildingPart_relative_to_water_result;
ecitygml_BuildingPart_relative_to_water_result ecitygml_BuildingPart_relative_to_water(const BuildingPart* self);

ExternalReferenceIterator* ecitygml_BuildingPart_external_references(const BuildingPart* self);

GenericAttributeKindIterator* ecitygml_BuildingPart_generic_attributes(const BuildingPart* self);

CityObjectRelationPropertyIterator* ecitygml_BuildingPart_related_to(const BuildingPart* self);

typedef struct ecitygml_BuildingPart_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_BuildingPart_space_type_result;
ecitygml_BuildingPart_space_type_result ecitygml_BuildingPart_space_type(const BuildingPart* self);

const SolidProperty* ecitygml_BuildingPart_lod1_solid(const BuildingPart* self);

const SolidProperty* ecitygml_BuildingPart_lod2_solid(const BuildingPart* self);

const SolidProperty* ecitygml_BuildingPart_lod3_solid(const BuildingPart* self);

const MultiSurfaceProperty* ecitygml_BuildingPart_lod0_multi_surface(const BuildingPart* self);

const MultiSurfaceProperty* ecitygml_BuildingPart_lod2_multi_surface(const BuildingPart* self);

const MultiSurfaceProperty* ecitygml_BuildingPart_lod3_multi_surface(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod0_multi_curve(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod2_multi_curve(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod3_multi_curve(const BuildingPart* self);

const PointProperty* ecitygml_BuildingPart_lod0_point(const BuildingPart* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_BuildingPart_boundaries(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod1_terrain_intersection_curve(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod2_terrain_intersection_curve(const BuildingPart* self);

const MultiCurveProperty* ecitygml_BuildingPart_lod3_terrain_intersection_curve(const BuildingPart* self);

const ImplicitGeometryProperty* ecitygml_BuildingPart_lod1_implicit_representation(const BuildingPart* self);

const ImplicitGeometryProperty* ecitygml_BuildingPart_lod2_implicit_representation(const BuildingPart* self);

const ImplicitGeometryProperty* ecitygml_BuildingPart_lod3_implicit_representation(const BuildingPart* self);

const Date* ecitygml_BuildingPart_date_of_construction(const BuildingPart* self);

const Date* ecitygml_BuildingPart_date_of_demolition(const BuildingPart* self);

HeightIterator* ecitygml_BuildingPart_heights(const BuildingPart* self);

OccupancyIterator* ecitygml_BuildingPart_occupancies(const BuildingPart* self);

const BuildingClassValue* ecitygml_BuildingPart_class(const BuildingPart* self);

BuildingFunctionValueIterator* ecitygml_BuildingPart_functions(const BuildingPart* self);

BuildingUsageValueIterator* ecitygml_BuildingPart_usages(const BuildingPart* self);

const RoofTypeValue* ecitygml_BuildingPart_roof_type(const BuildingPart* self);

typedef struct ecitygml_BuildingPart_storeys_above_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_BuildingPart_storeys_above_ground_result;
ecitygml_BuildingPart_storeys_above_ground_result ecitygml_BuildingPart_storeys_above_ground(const BuildingPart* self);

typedef struct ecitygml_BuildingPart_storeys_below_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_BuildingPart_storeys_below_ground_result;
ecitygml_BuildingPart_storeys_below_ground_result ecitygml_BuildingPart_storeys_below_ground(const BuildingPart* self);

AbstractBuildingSubdivisionPropertyIterator* ecitygml_BuildingPart_building_subdivisions(const BuildingPart* self);

const BuildingPart* ecitygml_BuildingPart_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_BuildingPart_destroy(BuildingPart* self);





#endif // BuildingPart_H
