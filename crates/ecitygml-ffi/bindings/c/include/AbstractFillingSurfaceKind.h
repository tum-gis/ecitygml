#ifndef AbstractFillingSurfaceKind_H
#define AbstractFillingSurfaceKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "FeatureType.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"

#include "AbstractFillingSurfaceKind.d.h"






const Id* ecitygml_AbstractFillingSurfaceKind_id(const AbstractFillingSurfaceKind* self);

CodeIterator* ecitygml_AbstractFillingSurfaceKind_names(const AbstractFillingSurfaceKind* self);

const BoundingShape* ecitygml_AbstractFillingSurfaceKind_bounded_by(const AbstractFillingSurfaceKind* self);

const Id* ecitygml_AbstractFillingSurfaceKind_feature_id(const AbstractFillingSurfaceKind* self);

const DateTime* ecitygml_AbstractFillingSurfaceKind_creation_date(const AbstractFillingSurfaceKind* self);

const DateTime* ecitygml_AbstractFillingSurfaceKind_termination_date(const AbstractFillingSurfaceKind* self);

const DateTime* ecitygml_AbstractFillingSurfaceKind_valid_from(const AbstractFillingSurfaceKind* self);

const DateTime* ecitygml_AbstractFillingSurfaceKind_valid_to(const AbstractFillingSurfaceKind* self);

typedef struct ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result;
ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result ecitygml_AbstractFillingSurfaceKind_relative_to_terrain(const AbstractFillingSurfaceKind* self);

typedef struct ecitygml_AbstractFillingSurfaceKind_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractFillingSurfaceKind_relative_to_water_result;
ecitygml_AbstractFillingSurfaceKind_relative_to_water_result ecitygml_AbstractFillingSurfaceKind_relative_to_water(const AbstractFillingSurfaceKind* self);

ExternalReferenceIterator* ecitygml_AbstractFillingSurfaceKind_external_references(const AbstractFillingSurfaceKind* self);

GenericAttributeKindIterator* ecitygml_AbstractFillingSurfaceKind_generic_attributes(const AbstractFillingSurfaceKind* self);

CityObjectRelationPropertyIterator* ecitygml_AbstractFillingSurfaceKind_related_to(const AbstractFillingSurfaceKind* self);

const MultiCurveProperty* ecitygml_AbstractFillingSurfaceKind_lod0_multi_curve(const AbstractFillingSurfaceKind* self);

const MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod0_multi_surface(const AbstractFillingSurfaceKind* self);

const MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod1_multi_surface(const AbstractFillingSurfaceKind* self);

const MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod2_multi_surface(const AbstractFillingSurfaceKind* self);

const MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(const AbstractFillingSurfaceKind* self);

FeatureType ecitygml_AbstractFillingSurfaceKind_feature_type(const AbstractFillingSurfaceKind* self);

void ecitygml_AbstractFillingSurfaceKind_destroy(AbstractFillingSurfaceKind* self);





#endif // AbstractFillingSurfaceKind_H
