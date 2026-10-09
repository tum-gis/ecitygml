#ifndef Section_H
#define Section_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractSpaceBoundaryPropertyIterator.d.h"
#include "AuxiliaryTrafficSpacePropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "HolePropertyIterator.d.h"
#include "Id.d.h"
#include "MarkingPropertyIterator.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "OccupancyIterator.d.h"
#include "PointProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"
#include "SectionClassValue.d.h"
#include "SolidProperty.d.h"
#include "SpaceType.d.h"
#include "TrafficDirectionValue.d.h"
#include "TrafficSpacePropertyIterator.d.h"

#include "Section.d.h"






const Id* ecitygml_Section_id(const Section* self);

CodeIterator* ecitygml_Section_names(const Section* self);

const BoundingShape* ecitygml_Section_bounded_by(const Section* self);

const Id* ecitygml_Section_feature_id(const Section* self);

const DateTime* ecitygml_Section_creation_date(const Section* self);

const DateTime* ecitygml_Section_termination_date(const Section* self);

const DateTime* ecitygml_Section_valid_from(const Section* self);

const DateTime* ecitygml_Section_valid_to(const Section* self);

typedef struct ecitygml_Section_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Section_relative_to_terrain_result;
ecitygml_Section_relative_to_terrain_result ecitygml_Section_relative_to_terrain(const Section* self);

typedef struct ecitygml_Section_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Section_relative_to_water_result;
ecitygml_Section_relative_to_water_result ecitygml_Section_relative_to_water(const Section* self);

ExternalReferenceIterator* ecitygml_Section_external_references(const Section* self);

GenericAttributeKindIterator* ecitygml_Section_generic_attributes(const Section* self);

CityObjectRelationPropertyIterator* ecitygml_Section_related_to(const Section* self);

typedef struct ecitygml_Section_space_type_result {union {SpaceType ok; }; bool is_ok;} ecitygml_Section_space_type_result;
ecitygml_Section_space_type_result ecitygml_Section_space_type(const Section* self);

const SolidProperty* ecitygml_Section_lod1_solid(const Section* self);

const SolidProperty* ecitygml_Section_lod2_solid(const Section* self);

const SolidProperty* ecitygml_Section_lod3_solid(const Section* self);

const MultiSurfaceProperty* ecitygml_Section_lod0_multi_surface(const Section* self);

const MultiSurfaceProperty* ecitygml_Section_lod2_multi_surface(const Section* self);

const MultiSurfaceProperty* ecitygml_Section_lod3_multi_surface(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod0_multi_curve(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod2_multi_curve(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod3_multi_curve(const Section* self);

const PointProperty* ecitygml_Section_lod0_point(const Section* self);

AbstractSpaceBoundaryPropertyIterator* ecitygml_Section_boundaries(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod1_terrain_intersection_curve(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod2_terrain_intersection_curve(const Section* self);

const MultiCurveProperty* ecitygml_Section_lod3_terrain_intersection_curve(const Section* self);

typedef struct ecitygml_Section_traffic_direction_result {union {TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Section_traffic_direction_result;
ecitygml_Section_traffic_direction_result ecitygml_Section_traffic_direction(const Section* self);

OccupancyIterator* ecitygml_Section_occupancies(const Section* self);

TrafficSpacePropertyIterator* ecitygml_Section_traffic_spaces(const Section* self);

AuxiliaryTrafficSpacePropertyIterator* ecitygml_Section_auxiliary_traffic_spaces(const Section* self);

MarkingPropertyIterator* ecitygml_Section_markings(const Section* self);

HolePropertyIterator* ecitygml_Section_holes(const Section* self);

const Section* ecitygml_Section_try_from(const AbstractFeatureKindRef* feature);

const SectionClassValue* ecitygml_Section_class(const Section* self);

void ecitygml_Section_destroy(Section* self);





#endif // Section_H
