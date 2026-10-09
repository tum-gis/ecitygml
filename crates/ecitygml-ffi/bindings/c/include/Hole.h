#ifndef Hole_H
#define Hole_H

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
#include "HoleClassValue.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"

#include "Hole.d.h"






const Id* ecitygml_Hole_id(const Hole* self);

CodeIterator* ecitygml_Hole_names(const Hole* self);

const BoundingShape* ecitygml_Hole_bounded_by(const Hole* self);

const Id* ecitygml_Hole_feature_id(const Hole* self);

const DateTime* ecitygml_Hole_creation_date(const Hole* self);

const DateTime* ecitygml_Hole_termination_date(const Hole* self);

const DateTime* ecitygml_Hole_valid_from(const Hole* self);

const DateTime* ecitygml_Hole_valid_to(const Hole* self);

typedef struct ecitygml_Hole_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Hole_relative_to_terrain_result;
ecitygml_Hole_relative_to_terrain_result ecitygml_Hole_relative_to_terrain(const Hole* self);

typedef struct ecitygml_Hole_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Hole_relative_to_water_result;
ecitygml_Hole_relative_to_water_result ecitygml_Hole_relative_to_water(const Hole* self);

ExternalReferenceIterator* ecitygml_Hole_external_references(const Hole* self);

GenericAttributeKindIterator* ecitygml_Hole_generic_attributes(const Hole* self);

CityObjectRelationPropertyIterator* ecitygml_Hole_related_to(const Hole* self);

typedef struct ecitygml_Hole_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Hole_space_type_result;
ecitygml_Hole_space_type_result ecitygml_Hole_space_type(const Hole* self);

const SolidProperty* ecitygml_Hole_lod1_solid(const Hole* self);

const SolidProperty* ecitygml_Hole_lod2_solid(const Hole* self);

const SolidProperty* ecitygml_Hole_lod3_solid(const Hole* self);

const MultiSurfaceProperty* ecitygml_Hole_lod0_multi_surface(const Hole* self);

const MultiSurfaceProperty* ecitygml_Hole_lod2_multi_surface(const Hole* self);

const MultiSurfaceProperty* ecitygml_Hole_lod3_multi_surface(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod0_multi_curve(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod2_multi_curve(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod3_multi_curve(const Hole* self);

const PointProperty* ecitygml_Hole_lod0_point(const Hole* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Hole_boundaries(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod1_terrain_intersection_curve(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod2_terrain_intersection_curve(const Hole* self);

const MultiCurveProperty* ecitygml_Hole_lod3_terrain_intersection_curve(const Hole* self);

const Hole* ecitygml_Hole_try_from(const AbstractFeatureKindRef* feature);

const HoleClassValue* ecitygml_Hole_class(const Hole* self);

void ecitygml_Hole_destroy(Hole* self);





#endif // Hole_H
