#ifndef Tunnel_H
#define Tunnel_H

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
#include "TunnelPartPropertyIterator.d.h"
#include "TunnelUsageValueIterator.d.h"

#include "Tunnel.d.h"






const Id* ecitygml_Tunnel_id(const Tunnel* self);

CodeIterator* ecitygml_Tunnel_names(const Tunnel* self);

const BoundingShape* ecitygml_Tunnel_bounded_by(const Tunnel* self);

const Id* ecitygml_Tunnel_feature_id(const Tunnel* self);

const DateTime* ecitygml_Tunnel_creation_date(const Tunnel* self);

const DateTime* ecitygml_Tunnel_termination_date(const Tunnel* self);

const DateTime* ecitygml_Tunnel_valid_from(const Tunnel* self);

const DateTime* ecitygml_Tunnel_valid_to(const Tunnel* self);

typedef struct ecitygml_Tunnel_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Tunnel_relative_to_terrain_result;
ecitygml_Tunnel_relative_to_terrain_result ecitygml_Tunnel_relative_to_terrain(const Tunnel* self);

typedef struct ecitygml_Tunnel_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Tunnel_relative_to_water_result;
ecitygml_Tunnel_relative_to_water_result ecitygml_Tunnel_relative_to_water(const Tunnel* self);

ExternalReferenceIterator* ecitygml_Tunnel_external_references(const Tunnel* self);

GenericAttributeKindIterator* ecitygml_Tunnel_generic_attributes(const Tunnel* self);

CityObjectRelationPropertyIterator* ecitygml_Tunnel_related_to(const Tunnel* self);

typedef struct ecitygml_Tunnel_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Tunnel_space_type_result;
ecitygml_Tunnel_space_type_result ecitygml_Tunnel_space_type(const Tunnel* self);

const SolidProperty* ecitygml_Tunnel_lod1_solid(const Tunnel* self);

const SolidProperty* ecitygml_Tunnel_lod2_solid(const Tunnel* self);

const SolidProperty* ecitygml_Tunnel_lod3_solid(const Tunnel* self);

const MultiSurfaceProperty* ecitygml_Tunnel_lod0_multi_surface(const Tunnel* self);

const MultiSurfaceProperty* ecitygml_Tunnel_lod2_multi_surface(const Tunnel* self);

const MultiSurfaceProperty* ecitygml_Tunnel_lod3_multi_surface(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod0_multi_curve(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod2_multi_curve(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod3_multi_curve(const Tunnel* self);

const PointProperty* ecitygml_Tunnel_lod0_point(const Tunnel* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Tunnel_boundaries(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod1_terrain_intersection_curve(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod2_terrain_intersection_curve(const Tunnel* self);

const MultiCurveProperty* ecitygml_Tunnel_lod3_terrain_intersection_curve(const Tunnel* self);

const ImplicitGeometryProperty* ecitygml_Tunnel_lod1_implicit_representation(const Tunnel* self);

const ImplicitGeometryProperty* ecitygml_Tunnel_lod2_implicit_representation(const Tunnel* self);

const ImplicitGeometryProperty* ecitygml_Tunnel_lod3_implicit_representation(const Tunnel* self);

const Date* ecitygml_Tunnel_date_of_construction(const Tunnel* self);

const Date* ecitygml_Tunnel_date_of_demolition(const Tunnel* self);

HeightIterator* ecitygml_Tunnel_heights(const Tunnel* self);

OccupancyIterator* ecitygml_Tunnel_occupancies(const Tunnel* self);

const TunnelClassValue* ecitygml_Tunnel_class(const Tunnel* self);

TunnelFunctionValueIterator* ecitygml_Tunnel_functions(const Tunnel* self);

TunnelUsageValueIterator* ecitygml_Tunnel_usages(const Tunnel* self);

const Tunnel* ecitygml_Tunnel_try_from(const AbstractFeatureKindRef* feature);

TunnelPartPropertyIterator* ecitygml_Tunnel_tunnel_parts(const Tunnel* self);

void ecitygml_Tunnel_destroy(Tunnel* self);





#endif // Tunnel_H
