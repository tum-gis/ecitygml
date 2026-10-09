#ifndef PlantCover_H
#define PlantCover_H

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
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "ImplicitGeometryProperty.d.h"
#include "Measure.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "PlantCoverClassValue.d.h"
#include "PlantCoverFunctionValueIterator.d.h"
#include "PlantCoverUsageValueIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "PlantCover.d.h"






const Id* ecitygml_PlantCover_id(const PlantCover* self);

CodeIterator* ecitygml_PlantCover_names(const PlantCover* self);

const BoundingShape* ecitygml_PlantCover_bounded_by(const PlantCover* self);

const Id* ecitygml_PlantCover_feature_id(const PlantCover* self);

const DateTime* ecitygml_PlantCover_creation_date(const PlantCover* self);

const DateTime* ecitygml_PlantCover_termination_date(const PlantCover* self);

const DateTime* ecitygml_PlantCover_valid_from(const PlantCover* self);

const DateTime* ecitygml_PlantCover_valid_to(const PlantCover* self);

typedef struct ecitygml_PlantCover_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_PlantCover_relative_to_terrain_result;
ecitygml_PlantCover_relative_to_terrain_result ecitygml_PlantCover_relative_to_terrain(const PlantCover* self);

typedef struct ecitygml_PlantCover_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_PlantCover_relative_to_water_result;
ecitygml_PlantCover_relative_to_water_result ecitygml_PlantCover_relative_to_water(const PlantCover* self);

ExternalReferenceIterator* ecitygml_PlantCover_external_references(const PlantCover* self);

GenericAttributeKindIterator* ecitygml_PlantCover_generic_attributes(const PlantCover* self);

CityObjectRelationPropertyIterator* ecitygml_PlantCover_related_to(const PlantCover* self);

typedef struct ecitygml_PlantCover_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_PlantCover_space_type_result;
ecitygml_PlantCover_space_type_result ecitygml_PlantCover_space_type(const PlantCover* self);

const SolidProperty* ecitygml_PlantCover_lod1_solid(const PlantCover* self);

const SolidProperty* ecitygml_PlantCover_lod2_solid(const PlantCover* self);

const SolidProperty* ecitygml_PlantCover_lod3_solid(const PlantCover* self);

const MultiSurfaceProperty* ecitygml_PlantCover_lod0_multi_surface(const PlantCover* self);

const MultiSurfaceProperty* ecitygml_PlantCover_lod2_multi_surface(const PlantCover* self);

const MultiSurfaceProperty* ecitygml_PlantCover_lod3_multi_surface(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod0_multi_curve(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod2_multi_curve(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod3_multi_curve(const PlantCover* self);

const PointProperty* ecitygml_PlantCover_lod0_point(const PlantCover* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_PlantCover_boundaries(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod1_terrain_intersection_curve(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod2_terrain_intersection_curve(const PlantCover* self);

const MultiCurveProperty* ecitygml_PlantCover_lod3_terrain_intersection_curve(const PlantCover* self);

const ImplicitGeometryProperty* ecitygml_PlantCover_lod1_implicit_representation(const PlantCover* self);

const ImplicitGeometryProperty* ecitygml_PlantCover_lod2_implicit_representation(const PlantCover* self);

const ImplicitGeometryProperty* ecitygml_PlantCover_lod3_implicit_representation(const PlantCover* self);

const PlantCover* ecitygml_PlantCover_try_from(const AbstractFeatureKindRef* feature);

const PlantCoverClassValue* ecitygml_PlantCover_class(const PlantCover* self);

PlantCoverFunctionValueIterator* ecitygml_PlantCover_functions(const PlantCover* self);

PlantCoverUsageValueIterator* ecitygml_PlantCover_usages(const PlantCover* self);

const Measure* ecitygml_PlantCover_average_height(const PlantCover* self);

const Measure* ecitygml_PlantCover_min_height(const PlantCover* self);

const Measure* ecitygml_PlantCover_max_height(const PlantCover* self);

void ecitygml_PlantCover_destroy(PlantCover* self);





#endif // PlantCover_H
