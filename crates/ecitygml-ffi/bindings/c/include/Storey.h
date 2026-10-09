#ifndef Storey_H
#define Storey_H

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

#include "Storey.d.h"






const Id* ecitygml_Storey_id(const Storey* self);

CodeIterator* ecitygml_Storey_names(const Storey* self);

const BoundingShape* ecitygml_Storey_bounded_by(const Storey* self);

const Id* ecitygml_Storey_feature_id(const Storey* self);

const DateTime* ecitygml_Storey_creation_date(const Storey* self);

const DateTime* ecitygml_Storey_termination_date(const Storey* self);

const DateTime* ecitygml_Storey_valid_from(const Storey* self);

const DateTime* ecitygml_Storey_valid_to(const Storey* self);

typedef struct ecitygml_Storey_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Storey_relative_to_terrain_result;
ecitygml_Storey_relative_to_terrain_result ecitygml_Storey_relative_to_terrain(const Storey* self);

typedef struct ecitygml_Storey_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Storey_relative_to_water_result;
ecitygml_Storey_relative_to_water_result ecitygml_Storey_relative_to_water(const Storey* self);

ExternalReferenceIterator* ecitygml_Storey_external_references(const Storey* self);

GenericAttributeKindIterator* ecitygml_Storey_generic_attributes(const Storey* self);

CityObjectRelationPropertyIterator* ecitygml_Storey_related_to(const Storey* self);

typedef struct ecitygml_Storey_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Storey_space_type_result;
ecitygml_Storey_space_type_result ecitygml_Storey_space_type(const Storey* self);

const SolidProperty* ecitygml_Storey_lod1_solid(const Storey* self);

const SolidProperty* ecitygml_Storey_lod2_solid(const Storey* self);

const SolidProperty* ecitygml_Storey_lod3_solid(const Storey* self);

const MultiSurfaceProperty* ecitygml_Storey_lod0_multi_surface(const Storey* self);

const MultiSurfaceProperty* ecitygml_Storey_lod2_multi_surface(const Storey* self);

const MultiSurfaceProperty* ecitygml_Storey_lod3_multi_surface(const Storey* self);

const MultiCurveProperty* ecitygml_Storey_lod0_multi_curve(const Storey* self);

const MultiCurveProperty* ecitygml_Storey_lod2_multi_curve(const Storey* self);

const MultiCurveProperty* ecitygml_Storey_lod3_multi_curve(const Storey* self);

const PointProperty* ecitygml_Storey_lod0_point(const Storey* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Storey_boundaries(const Storey* self);

const BuildingSubdivisionClassValue* ecitygml_Storey_class(const Storey* self);

BuildingSubdivisionFunctionValueIterator* ecitygml_Storey_functions(const Storey* self);

BuildingSubdivisionUsageValueIterator* ecitygml_Storey_usages(const Storey* self);

const Storey* ecitygml_Storey_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_Storey_destroy(Storey* self);





#endif // Storey_H
