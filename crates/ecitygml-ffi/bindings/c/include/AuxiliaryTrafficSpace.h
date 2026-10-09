#ifndef AuxiliaryTrafficSpace_H
#define AuxiliaryTrafficSpace_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "AuxiliaryTrafficSpaceClassValue.d.h"
#include "AuxiliaryTrafficSpaceFunctionValueIterator.d.h"
#include "AuxiliaryTrafficSpaceUsageValueIterator.d.h"
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
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "AuxiliaryTrafficSpace.d.h"






const Id* ecitygml_AuxiliaryTrafficSpace_id(const AuxiliaryTrafficSpace* self);

CodeIterator* ecitygml_AuxiliaryTrafficSpace_names(const AuxiliaryTrafficSpace* self);

const BoundingShape* ecitygml_AuxiliaryTrafficSpace_bounded_by(const AuxiliaryTrafficSpace* self);

const Id* ecitygml_AuxiliaryTrafficSpace_feature_id(const AuxiliaryTrafficSpace* self);

const DateTime* ecitygml_AuxiliaryTrafficSpace_creation_date(const AuxiliaryTrafficSpace* self);

const DateTime* ecitygml_AuxiliaryTrafficSpace_termination_date(const AuxiliaryTrafficSpace* self);

const DateTime* ecitygml_AuxiliaryTrafficSpace_valid_from(const AuxiliaryTrafficSpace* self);

const DateTime* ecitygml_AuxiliaryTrafficSpace_valid_to(const AuxiliaryTrafficSpace* self);

typedef struct ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result;
ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result ecitygml_AuxiliaryTrafficSpace_relative_to_terrain(const AuxiliaryTrafficSpace* self);

typedef struct ecitygml_AuxiliaryTrafficSpace_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_relative_to_water_result;
ecitygml_AuxiliaryTrafficSpace_relative_to_water_result ecitygml_AuxiliaryTrafficSpace_relative_to_water(const AuxiliaryTrafficSpace* self);

ExternalReferenceIterator* ecitygml_AuxiliaryTrafficSpace_external_references(const AuxiliaryTrafficSpace* self);

GenericAttributeKindIterator* ecitygml_AuxiliaryTrafficSpace_generic_attributes(const AuxiliaryTrafficSpace* self);

CityObjectRelationPropertyIterator* ecitygml_AuxiliaryTrafficSpace_related_to(const AuxiliaryTrafficSpace* self);

typedef struct ecitygml_AuxiliaryTrafficSpace_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_space_type_result;
ecitygml_AuxiliaryTrafficSpace_space_type_result ecitygml_AuxiliaryTrafficSpace_space_type(const AuxiliaryTrafficSpace* self);

const SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod1_solid(const AuxiliaryTrafficSpace* self);

const SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod2_solid(const AuxiliaryTrafficSpace* self);

const SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod3_solid(const AuxiliaryTrafficSpace* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod0_multi_surface(const AuxiliaryTrafficSpace* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod2_multi_surface(const AuxiliaryTrafficSpace* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod3_multi_surface(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod0_multi_curve(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod2_multi_curve(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod3_multi_curve(const AuxiliaryTrafficSpace* self);

const PointProperty* ecitygml_AuxiliaryTrafficSpace_lod0_point(const AuxiliaryTrafficSpace* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_AuxiliaryTrafficSpace_boundaries(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod1_terrain_intersection_curve(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod2_terrain_intersection_curve(const AuxiliaryTrafficSpace* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod3_terrain_intersection_curve(const AuxiliaryTrafficSpace* self);

const AuxiliaryTrafficSpace* ecitygml_AuxiliaryTrafficSpace_try_from(const AbstractFeatureKindRef* feature);

const AuxiliaryTrafficSpaceClassValue* ecitygml_AuxiliaryTrafficSpace_class(const AuxiliaryTrafficSpace* self);

AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml_AuxiliaryTrafficSpace_functions(const AuxiliaryTrafficSpace* self);

AuxiliaryTrafficSpaceUsageValueIterator* ecitygml_AuxiliaryTrafficSpace_usages(const AuxiliaryTrafficSpace* self);

GranularityValue ecitygml_AuxiliaryTrafficSpace_granularity(const AuxiliaryTrafficSpace* self);

void ecitygml_AuxiliaryTrafficSpace_destroy(AuxiliaryTrafficSpace* self);





#endif // AuxiliaryTrafficSpace_H
