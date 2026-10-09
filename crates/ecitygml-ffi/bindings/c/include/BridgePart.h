#ifndef BridgePart_H
#define BridgePart_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "BridgeClassValue.d.h"
#include "BridgeFunctionValueIterator.d.h"
#include "BridgeUsageValueIterator.d.h"
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
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "BridgePart.d.h"






const Id* ecitygml_BridgePart_id(const BridgePart* self);

CodeIterator* ecitygml_BridgePart_names(const BridgePart* self);

const BoundingShape* ecitygml_BridgePart_bounded_by(const BridgePart* self);

const Id* ecitygml_BridgePart_feature_id(const BridgePart* self);

const DateTime* ecitygml_BridgePart_creation_date(const BridgePart* self);

const DateTime* ecitygml_BridgePart_termination_date(const BridgePart* self);

const DateTime* ecitygml_BridgePart_valid_from(const BridgePart* self);

const DateTime* ecitygml_BridgePart_valid_to(const BridgePart* self);

typedef struct ecitygml_BridgePart_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_BridgePart_relative_to_terrain_result;
ecitygml_BridgePart_relative_to_terrain_result ecitygml_BridgePart_relative_to_terrain(const BridgePart* self);

typedef struct ecitygml_BridgePart_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_BridgePart_relative_to_water_result;
ecitygml_BridgePart_relative_to_water_result ecitygml_BridgePart_relative_to_water(const BridgePart* self);

ExternalReferenceIterator* ecitygml_BridgePart_external_references(const BridgePart* self);

GenericAttributeKindIterator* ecitygml_BridgePart_generic_attributes(const BridgePart* self);

CityObjectRelationPropertyIterator* ecitygml_BridgePart_related_to(const BridgePart* self);

typedef struct ecitygml_BridgePart_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_BridgePart_space_type_result;
ecitygml_BridgePart_space_type_result ecitygml_BridgePart_space_type(const BridgePart* self);

const SolidProperty* ecitygml_BridgePart_lod1_solid(const BridgePart* self);

const SolidProperty* ecitygml_BridgePart_lod2_solid(const BridgePart* self);

const SolidProperty* ecitygml_BridgePart_lod3_solid(const BridgePart* self);

const MultiSurfaceProperty* ecitygml_BridgePart_lod0_multi_surface(const BridgePart* self);

const MultiSurfaceProperty* ecitygml_BridgePart_lod2_multi_surface(const BridgePart* self);

const MultiSurfaceProperty* ecitygml_BridgePart_lod3_multi_surface(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod0_multi_curve(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod2_multi_curve(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod3_multi_curve(const BridgePart* self);

const PointProperty* ecitygml_BridgePart_lod0_point(const BridgePart* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_BridgePart_boundaries(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod1_terrain_intersection_curve(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod2_terrain_intersection_curve(const BridgePart* self);

const MultiCurveProperty* ecitygml_BridgePart_lod3_terrain_intersection_curve(const BridgePart* self);

const ImplicitGeometryProperty* ecitygml_BridgePart_lod1_implicit_representation(const BridgePart* self);

const ImplicitGeometryProperty* ecitygml_BridgePart_lod2_implicit_representation(const BridgePart* self);

const ImplicitGeometryProperty* ecitygml_BridgePart_lod3_implicit_representation(const BridgePart* self);

const Date* ecitygml_BridgePart_date_of_construction(const BridgePart* self);

const Date* ecitygml_BridgePart_date_of_demolition(const BridgePart* self);

HeightIterator* ecitygml_BridgePart_heights(const BridgePart* self);

OccupancyIterator* ecitygml_BridgePart_occupancies(const BridgePart* self);

const BridgeClassValue* ecitygml_BridgePart_class(const BridgePart* self);

BridgeFunctionValueIterator* ecitygml_BridgePart_functions(const BridgePart* self);

BridgeUsageValueIterator* ecitygml_BridgePart_usages(const BridgePart* self);

typedef struct ecitygml_BridgePart_is_movable_result {union {bool ok; }; bool is_ok;} ecitygml_BridgePart_is_movable_result;
ecitygml_BridgePart_is_movable_result ecitygml_BridgePart_is_movable(const BridgePart* self);

const BridgePart* ecitygml_BridgePart_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_BridgePart_destroy(BridgePart* self);





#endif // BridgePart_H
