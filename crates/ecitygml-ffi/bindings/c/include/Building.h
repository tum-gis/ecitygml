#ifndef Building_H
#define Building_H

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
#include "BuildingPartPropertyIterator.d.h"
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

#include "Building.d.h"






const Id* ecitygml_Building_id(const Building* self);

CodeIterator* ecitygml_Building_names(const Building* self);

const BoundingShape* ecitygml_Building_bounded_by(const Building* self);

const Id* ecitygml_Building_feature_id(const Building* self);

const DateTime* ecitygml_Building_creation_date(const Building* self);

const DateTime* ecitygml_Building_termination_date(const Building* self);

const DateTime* ecitygml_Building_valid_from(const Building* self);

const DateTime* ecitygml_Building_valid_to(const Building* self);

typedef struct ecitygml_Building_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Building_relative_to_terrain_result;
ecitygml_Building_relative_to_terrain_result ecitygml_Building_relative_to_terrain(const Building* self);

typedef struct ecitygml_Building_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Building_relative_to_water_result;
ecitygml_Building_relative_to_water_result ecitygml_Building_relative_to_water(const Building* self);

ExternalReferenceIterator* ecitygml_Building_external_references(const Building* self);

GenericAttributeKindIterator* ecitygml_Building_generic_attributes(const Building* self);

CityObjectRelationPropertyIterator* ecitygml_Building_related_to(const Building* self);

typedef struct ecitygml_Building_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Building_space_type_result;
ecitygml_Building_space_type_result ecitygml_Building_space_type(const Building* self);

const SolidProperty* ecitygml_Building_lod1_solid(const Building* self);

const SolidProperty* ecitygml_Building_lod2_solid(const Building* self);

const SolidProperty* ecitygml_Building_lod3_solid(const Building* self);

const MultiSurfaceProperty* ecitygml_Building_lod0_multi_surface(const Building* self);

const MultiSurfaceProperty* ecitygml_Building_lod2_multi_surface(const Building* self);

const MultiSurfaceProperty* ecitygml_Building_lod3_multi_surface(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod0_multi_curve(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod2_multi_curve(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod3_multi_curve(const Building* self);

const PointProperty* ecitygml_Building_lod0_point(const Building* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Building_boundaries(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod1_terrain_intersection_curve(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod2_terrain_intersection_curve(const Building* self);

const MultiCurveProperty* ecitygml_Building_lod3_terrain_intersection_curve(const Building* self);

const ImplicitGeometryProperty* ecitygml_Building_lod1_implicit_representation(const Building* self);

const ImplicitGeometryProperty* ecitygml_Building_lod2_implicit_representation(const Building* self);

const ImplicitGeometryProperty* ecitygml_Building_lod3_implicit_representation(const Building* self);

const Date* ecitygml_Building_date_of_construction(const Building* self);

const Date* ecitygml_Building_date_of_demolition(const Building* self);

HeightIterator* ecitygml_Building_heights(const Building* self);

OccupancyIterator* ecitygml_Building_occupancies(const Building* self);

const BuildingClassValue* ecitygml_Building_class(const Building* self);

BuildingFunctionValueIterator* ecitygml_Building_functions(const Building* self);

BuildingUsageValueIterator* ecitygml_Building_usages(const Building* self);

const RoofTypeValue* ecitygml_Building_roof_type(const Building* self);

typedef struct ecitygml_Building_storeys_above_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_Building_storeys_above_ground_result;
ecitygml_Building_storeys_above_ground_result ecitygml_Building_storeys_above_ground(const Building* self);

typedef struct ecitygml_Building_storeys_below_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_Building_storeys_below_ground_result;
ecitygml_Building_storeys_below_ground_result ecitygml_Building_storeys_below_ground(const Building* self);

AbstractBuildingSubdivisionPropertyIterator* ecitygml_Building_building_subdivisions(const Building* self);

const Building* ecitygml_Building_try_from(const AbstractFeatureKindRef* feature);

BuildingPartPropertyIterator* ecitygml_Building_building_parts(const Building* self);

void ecitygml_Building_destroy(Building* self);





#endif // Building_H
