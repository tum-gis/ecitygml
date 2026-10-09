#ifndef CityFurniture_H
#define CityFurniture_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "CityFurnitureClassValue.d.h"
#include "CityFurnitureFunctionValueIterator.d.h"
#include "CityFurnitureUsageValueIterator.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "ImplicitGeometryProperty.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "CityFurniture.d.h"






const Id* ecitygml_CityFurniture_id(const CityFurniture* self);

CodeIterator* ecitygml_CityFurniture_names(const CityFurniture* self);

const BoundingShape* ecitygml_CityFurniture_bounded_by(const CityFurniture* self);

const Id* ecitygml_CityFurniture_feature_id(const CityFurniture* self);

const DateTime* ecitygml_CityFurniture_creation_date(const CityFurniture* self);

const DateTime* ecitygml_CityFurniture_termination_date(const CityFurniture* self);

const DateTime* ecitygml_CityFurniture_valid_from(const CityFurniture* self);

const DateTime* ecitygml_CityFurniture_valid_to(const CityFurniture* self);

typedef struct ecitygml_CityFurniture_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_CityFurniture_relative_to_terrain_result;
ecitygml_CityFurniture_relative_to_terrain_result ecitygml_CityFurniture_relative_to_terrain(const CityFurniture* self);

typedef struct ecitygml_CityFurniture_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_CityFurniture_relative_to_water_result;
ecitygml_CityFurniture_relative_to_water_result ecitygml_CityFurniture_relative_to_water(const CityFurniture* self);

ExternalReferenceIterator* ecitygml_CityFurniture_external_references(const CityFurniture* self);

GenericAttributeKindIterator* ecitygml_CityFurniture_generic_attributes(const CityFurniture* self);

CityObjectRelationPropertyIterator* ecitygml_CityFurniture_related_to(const CityFurniture* self);

typedef struct ecitygml_CityFurniture_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_CityFurniture_space_type_result;
ecitygml_CityFurniture_space_type_result ecitygml_CityFurniture_space_type(const CityFurniture* self);

const SolidProperty* ecitygml_CityFurniture_lod1_solid(const CityFurniture* self);

const SolidProperty* ecitygml_CityFurniture_lod2_solid(const CityFurniture* self);

const SolidProperty* ecitygml_CityFurniture_lod3_solid(const CityFurniture* self);

const MultiSurfaceProperty* ecitygml_CityFurniture_lod0_multi_surface(const CityFurniture* self);

const MultiSurfaceProperty* ecitygml_CityFurniture_lod2_multi_surface(const CityFurniture* self);

const MultiSurfaceProperty* ecitygml_CityFurniture_lod3_multi_surface(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod0_multi_curve(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod2_multi_curve(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod3_multi_curve(const CityFurniture* self);

const PointProperty* ecitygml_CityFurniture_lod0_point(const CityFurniture* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_CityFurniture_boundaries(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod1_terrain_intersection_curve(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod2_terrain_intersection_curve(const CityFurniture* self);

const MultiCurveProperty* ecitygml_CityFurniture_lod3_terrain_intersection_curve(const CityFurniture* self);

const ImplicitGeometryProperty* ecitygml_CityFurniture_lod1_implicit_representation(const CityFurniture* self);

const ImplicitGeometryProperty* ecitygml_CityFurniture_lod2_implicit_representation(const CityFurniture* self);

const ImplicitGeometryProperty* ecitygml_CityFurniture_lod3_implicit_representation(const CityFurniture* self);

const CityFurniture* ecitygml_CityFurniture_try_from(const AbstractFeatureKindRef* feature);

const CityFurnitureClassValue* ecitygml_CityFurniture_class(const CityFurniture* self);

CityFurnitureFunctionValueIterator* ecitygml_CityFurniture_functions(const CityFurniture* self);

CityFurnitureUsageValueIterator* ecitygml_CityFurniture_usages(const CityFurniture* self);

void ecitygml_CityFurniture_destroy(CityFurniture* self);





#endif // CityFurniture_H
