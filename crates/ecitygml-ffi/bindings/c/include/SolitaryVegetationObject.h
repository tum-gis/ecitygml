#ifndef SolitaryVegetationObject_H
#define SolitaryVegetationObject_H

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
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SolitaryVegetationObjectClassValue.d.h"
#include "SolitaryVegetationObjectFunctionValueIterator.d.h"
#include "SolitaryVegetationObjectUsageValueIterator.d.h"
#include "SpaceType.d.h"
#include "SpeciesValue.d.h"

#include "SolitaryVegetationObject.d.h"






const Id* ecitygml_SolitaryVegetationObject_id(const SolitaryVegetationObject* self);

CodeIterator* ecitygml_SolitaryVegetationObject_names(const SolitaryVegetationObject* self);

const BoundingShape* ecitygml_SolitaryVegetationObject_bounded_by(const SolitaryVegetationObject* self);

const Id* ecitygml_SolitaryVegetationObject_feature_id(const SolitaryVegetationObject* self);

const DateTime* ecitygml_SolitaryVegetationObject_creation_date(const SolitaryVegetationObject* self);

const DateTime* ecitygml_SolitaryVegetationObject_termination_date(const SolitaryVegetationObject* self);

const DateTime* ecitygml_SolitaryVegetationObject_valid_from(const SolitaryVegetationObject* self);

const DateTime* ecitygml_SolitaryVegetationObject_valid_to(const SolitaryVegetationObject* self);

typedef struct ecitygml_SolitaryVegetationObject_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_relative_to_terrain_result;
ecitygml_SolitaryVegetationObject_relative_to_terrain_result ecitygml_SolitaryVegetationObject_relative_to_terrain(const SolitaryVegetationObject* self);

typedef struct ecitygml_SolitaryVegetationObject_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_relative_to_water_result;
ecitygml_SolitaryVegetationObject_relative_to_water_result ecitygml_SolitaryVegetationObject_relative_to_water(const SolitaryVegetationObject* self);

ExternalReferenceIterator* ecitygml_SolitaryVegetationObject_external_references(const SolitaryVegetationObject* self);

GenericAttributeKindIterator* ecitygml_SolitaryVegetationObject_generic_attributes(const SolitaryVegetationObject* self);

CityObjectRelationPropertyIterator* ecitygml_SolitaryVegetationObject_related_to(const SolitaryVegetationObject* self);

typedef struct ecitygml_SolitaryVegetationObject_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_space_type_result;
ecitygml_SolitaryVegetationObject_space_type_result ecitygml_SolitaryVegetationObject_space_type(const SolitaryVegetationObject* self);

const SolidProperty* ecitygml_SolitaryVegetationObject_lod1_solid(const SolitaryVegetationObject* self);

const SolidProperty* ecitygml_SolitaryVegetationObject_lod2_solid(const SolitaryVegetationObject* self);

const SolidProperty* ecitygml_SolitaryVegetationObject_lod3_solid(const SolitaryVegetationObject* self);

const MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod0_multi_surface(const SolitaryVegetationObject* self);

const MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod2_multi_surface(const SolitaryVegetationObject* self);

const MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod3_multi_surface(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod0_multi_curve(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod2_multi_curve(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod3_multi_curve(const SolitaryVegetationObject* self);

const PointProperty* ecitygml_SolitaryVegetationObject_lod0_point(const SolitaryVegetationObject* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_SolitaryVegetationObject_boundaries(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod2_terrain_intersection_curve(const SolitaryVegetationObject* self);

const MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod3_terrain_intersection_curve(const SolitaryVegetationObject* self);

const ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod1_implicit_representation(const SolitaryVegetationObject* self);

const ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod2_implicit_representation(const SolitaryVegetationObject* self);

const ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod3_implicit_representation(const SolitaryVegetationObject* self);

const SolitaryVegetationObject* ecitygml_SolitaryVegetationObject_try_from(const AbstractFeatureKindRef* feature);

const SolitaryVegetationObjectClassValue* ecitygml_SolitaryVegetationObject_class(const SolitaryVegetationObject* self);

SolitaryVegetationObjectFunctionValueIterator* ecitygml_SolitaryVegetationObject_functions(const SolitaryVegetationObject* self);

SolitaryVegetationObjectUsageValueIterator* ecitygml_SolitaryVegetationObject_usages(const SolitaryVegetationObject* self);

const SpeciesValue* ecitygml_SolitaryVegetationObject_species(const SolitaryVegetationObject* self);

const Measure* ecitygml_SolitaryVegetationObject_height(const SolitaryVegetationObject* self);

const Measure* ecitygml_SolitaryVegetationObject_trunk_diameter(const SolitaryVegetationObject* self);

const Measure* ecitygml_SolitaryVegetationObject_crown_diameter(const SolitaryVegetationObject* self);

const Measure* ecitygml_SolitaryVegetationObject_root_ball_diameter(const SolitaryVegetationObject* self);

const Measure* ecitygml_SolitaryVegetationObject_max_root_ball_depth(const SolitaryVegetationObject* self);

void ecitygml_SolitaryVegetationObject_destroy(SolitaryVegetationObject* self);





#endif // SolitaryVegetationObject_H
