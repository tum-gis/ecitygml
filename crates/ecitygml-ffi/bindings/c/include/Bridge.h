#ifndef Bridge_H
#define Bridge_H

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
#include "BridgePartPropertyIterator.d.h"
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

#include "Bridge.d.h"






const Id* ecitygml_Bridge_id(const Bridge* self);

CodeIterator* ecitygml_Bridge_names(const Bridge* self);

const BoundingShape* ecitygml_Bridge_bounded_by(const Bridge* self);

const Id* ecitygml_Bridge_feature_id(const Bridge* self);

const DateTime* ecitygml_Bridge_creation_date(const Bridge* self);

const DateTime* ecitygml_Bridge_termination_date(const Bridge* self);

const DateTime* ecitygml_Bridge_valid_from(const Bridge* self);

const DateTime* ecitygml_Bridge_valid_to(const Bridge* self);

typedef struct ecitygml_Bridge_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Bridge_relative_to_terrain_result;
ecitygml_Bridge_relative_to_terrain_result ecitygml_Bridge_relative_to_terrain(const Bridge* self);

typedef struct ecitygml_Bridge_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Bridge_relative_to_water_result;
ecitygml_Bridge_relative_to_water_result ecitygml_Bridge_relative_to_water(const Bridge* self);

ExternalReferenceIterator* ecitygml_Bridge_external_references(const Bridge* self);

GenericAttributeKindIterator* ecitygml_Bridge_generic_attributes(const Bridge* self);

CityObjectRelationPropertyIterator* ecitygml_Bridge_related_to(const Bridge* self);

typedef struct ecitygml_Bridge_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Bridge_space_type_result;
ecitygml_Bridge_space_type_result ecitygml_Bridge_space_type(const Bridge* self);

const SolidProperty* ecitygml_Bridge_lod1_solid(const Bridge* self);

const SolidProperty* ecitygml_Bridge_lod2_solid(const Bridge* self);

const SolidProperty* ecitygml_Bridge_lod3_solid(const Bridge* self);

const MultiSurfaceProperty* ecitygml_Bridge_lod0_multi_surface(const Bridge* self);

const MultiSurfaceProperty* ecitygml_Bridge_lod2_multi_surface(const Bridge* self);

const MultiSurfaceProperty* ecitygml_Bridge_lod3_multi_surface(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod0_multi_curve(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod2_multi_curve(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod3_multi_curve(const Bridge* self);

const PointProperty* ecitygml_Bridge_lod0_point(const Bridge* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Bridge_boundaries(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod1_terrain_intersection_curve(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod2_terrain_intersection_curve(const Bridge* self);

const MultiCurveProperty* ecitygml_Bridge_lod3_terrain_intersection_curve(const Bridge* self);

const ImplicitGeometryProperty* ecitygml_Bridge_lod1_implicit_representation(const Bridge* self);

const ImplicitGeometryProperty* ecitygml_Bridge_lod2_implicit_representation(const Bridge* self);

const ImplicitGeometryProperty* ecitygml_Bridge_lod3_implicit_representation(const Bridge* self);

const Date* ecitygml_Bridge_date_of_construction(const Bridge* self);

const Date* ecitygml_Bridge_date_of_demolition(const Bridge* self);

HeightIterator* ecitygml_Bridge_heights(const Bridge* self);

OccupancyIterator* ecitygml_Bridge_occupancies(const Bridge* self);

const BridgeClassValue* ecitygml_Bridge_class(const Bridge* self);

BridgeFunctionValueIterator* ecitygml_Bridge_functions(const Bridge* self);

BridgeUsageValueIterator* ecitygml_Bridge_usages(const Bridge* self);

typedef struct ecitygml_Bridge_is_movable_result {union {bool ok; }; bool is_ok;} ecitygml_Bridge_is_movable_result;
ecitygml_Bridge_is_movable_result ecitygml_Bridge_is_movable(const Bridge* self);

const Bridge* ecitygml_Bridge_try_from(const AbstractFeatureKindRef* feature);

BridgePartPropertyIterator* ecitygml_Bridge_bridge_parts(const Bridge* self);

void ecitygml_Bridge_destroy(Bridge* self);





#endif // Bridge_H
