#ifndef BuildingUnit_H
#define BuildingUnit_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "BuildingSubdivisionClassValue.d.h"
#include "BuildingSubdivisionFunctionValueIterator.d.h"
#include "BuildingSubdivisionUsageValueIterator.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "BuildingUnit.d.h"






const Id* ecitygml_BuildingUnit_id(const BuildingUnit* self);

CodeIterator* ecitygml_BuildingUnit_names(const BuildingUnit* self);

const BoundingShape* ecitygml_BuildingUnit_bounded_by(const BuildingUnit* self);

const Id* ecitygml_BuildingUnit_feature_id(const BuildingUnit* self);

const DateTime* ecitygml_BuildingUnit_creation_date(const BuildingUnit* self);

const DateTime* ecitygml_BuildingUnit_termination_date(const BuildingUnit* self);

const DateTime* ecitygml_BuildingUnit_valid_from(const BuildingUnit* self);

const DateTime* ecitygml_BuildingUnit_valid_to(const BuildingUnit* self);

typedef struct ecitygml_BuildingUnit_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_BuildingUnit_relative_to_terrain_result;
ecitygml_BuildingUnit_relative_to_terrain_result ecitygml_BuildingUnit_relative_to_terrain(const BuildingUnit* self);

typedef struct ecitygml_BuildingUnit_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_BuildingUnit_relative_to_water_result;
ecitygml_BuildingUnit_relative_to_water_result ecitygml_BuildingUnit_relative_to_water(const BuildingUnit* self);

ExternalReferenceIterator* ecitygml_BuildingUnit_external_references(const BuildingUnit* self);

GenericAttributeKindIterator* ecitygml_BuildingUnit_generic_attributes(const BuildingUnit* self);

CityObjectRelationPropertyIterator* ecitygml_BuildingUnit_related_to(const BuildingUnit* self);

typedef struct ecitygml_BuildingUnit_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_BuildingUnit_space_type_result;
ecitygml_BuildingUnit_space_type_result ecitygml_BuildingUnit_space_type(const BuildingUnit* self);

const SolidProperty* ecitygml_BuildingUnit_lod1_solid(const BuildingUnit* self);

const SolidProperty* ecitygml_BuildingUnit_lod2_solid(const BuildingUnit* self);

const SolidProperty* ecitygml_BuildingUnit_lod3_solid(const BuildingUnit* self);

const MultiSurfaceProperty* ecitygml_BuildingUnit_lod0_multi_surface(const BuildingUnit* self);

const MultiSurfaceProperty* ecitygml_BuildingUnit_lod2_multi_surface(const BuildingUnit* self);

const MultiSurfaceProperty* ecitygml_BuildingUnit_lod3_multi_surface(const BuildingUnit* self);

const MultiCurveProperty* ecitygml_BuildingUnit_lod0_multi_curve(const BuildingUnit* self);

const MultiCurveProperty* ecitygml_BuildingUnit_lod2_multi_curve(const BuildingUnit* self);

const MultiCurveProperty* ecitygml_BuildingUnit_lod3_multi_curve(const BuildingUnit* self);

const PointProperty* ecitygml_BuildingUnit_lod0_point(const BuildingUnit* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_BuildingUnit_boundaries(const BuildingUnit* self);

const BuildingSubdivisionClassValue* ecitygml_BuildingUnit_class(const BuildingUnit* self);

BuildingSubdivisionFunctionValueIterator* ecitygml_BuildingUnit_functions(const BuildingUnit* self);

BuildingSubdivisionUsageValueIterator* ecitygml_BuildingUnit_usages(const BuildingUnit* self);

const BuildingUnit* ecitygml_BuildingUnit_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_BuildingUnit_destroy(BuildingUnit* self);





#endif // BuildingUnit_H
