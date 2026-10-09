#ifndef TunnelPart_H
#define TunnelPart_H

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
#include "TunnelClassValue.d.h"
#include "TunnelFunctionValueIterator.d.h"
#include "TunnelUsageValueIterator.d.h"

#include "TunnelPart.d.h"






const Id* ecitygml_TunnelPart_id(const TunnelPart* self);

CodeIterator* ecitygml_TunnelPart_names(const TunnelPart* self);

const BoundingShape* ecitygml_TunnelPart_bounded_by(const TunnelPart* self);

const Id* ecitygml_TunnelPart_feature_id(const TunnelPart* self);

const DateTime* ecitygml_TunnelPart_creation_date(const TunnelPart* self);

const DateTime* ecitygml_TunnelPart_termination_date(const TunnelPart* self);

const DateTime* ecitygml_TunnelPart_valid_from(const TunnelPart* self);

const DateTime* ecitygml_TunnelPart_valid_to(const TunnelPart* self);

typedef struct ecitygml_TunnelPart_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_TunnelPart_relative_to_terrain_result;
ecitygml_TunnelPart_relative_to_terrain_result ecitygml_TunnelPart_relative_to_terrain(const TunnelPart* self);

typedef struct ecitygml_TunnelPart_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_TunnelPart_relative_to_water_result;
ecitygml_TunnelPart_relative_to_water_result ecitygml_TunnelPart_relative_to_water(const TunnelPart* self);

ExternalReferenceIterator* ecitygml_TunnelPart_external_references(const TunnelPart* self);

GenericAttributeKindIterator* ecitygml_TunnelPart_generic_attributes(const TunnelPart* self);

CityObjectRelationPropertyIterator* ecitygml_TunnelPart_related_to(const TunnelPart* self);

typedef struct ecitygml_TunnelPart_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_TunnelPart_space_type_result;
ecitygml_TunnelPart_space_type_result ecitygml_TunnelPart_space_type(const TunnelPart* self);

const SolidProperty* ecitygml_TunnelPart_lod1_solid(const TunnelPart* self);

const SolidProperty* ecitygml_TunnelPart_lod2_solid(const TunnelPart* self);

const SolidProperty* ecitygml_TunnelPart_lod3_solid(const TunnelPart* self);

const MultiSurfaceProperty* ecitygml_TunnelPart_lod0_multi_surface(const TunnelPart* self);

const MultiSurfaceProperty* ecitygml_TunnelPart_lod2_multi_surface(const TunnelPart* self);

const MultiSurfaceProperty* ecitygml_TunnelPart_lod3_multi_surface(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod0_multi_curve(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod2_multi_curve(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod3_multi_curve(const TunnelPart* self);

const PointProperty* ecitygml_TunnelPart_lod0_point(const TunnelPart* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_TunnelPart_boundaries(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod1_terrain_intersection_curve(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod2_terrain_intersection_curve(const TunnelPart* self);

const MultiCurveProperty* ecitygml_TunnelPart_lod3_terrain_intersection_curve(const TunnelPart* self);

const ImplicitGeometryProperty* ecitygml_TunnelPart_lod1_implicit_representation(const TunnelPart* self);

const ImplicitGeometryProperty* ecitygml_TunnelPart_lod2_implicit_representation(const TunnelPart* self);

const ImplicitGeometryProperty* ecitygml_TunnelPart_lod3_implicit_representation(const TunnelPart* self);

const Date* ecitygml_TunnelPart_date_of_construction(const TunnelPart* self);

const Date* ecitygml_TunnelPart_date_of_demolition(const TunnelPart* self);

HeightIterator* ecitygml_TunnelPart_heights(const TunnelPart* self);

OccupancyIterator* ecitygml_TunnelPart_occupancies(const TunnelPart* self);

const TunnelClassValue* ecitygml_TunnelPart_class(const TunnelPart* self);

TunnelFunctionValueIterator* ecitygml_TunnelPart_functions(const TunnelPart* self);

TunnelUsageValueIterator* ecitygml_TunnelPart_usages(const TunnelPart* self);

const TunnelPart* ecitygml_TunnelPart_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_TunnelPart_destroy(TunnelPart* self);





#endif // TunnelPart_H
