#ifndef RoofSurface_H
#define RoofSurface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AbstractFillingSurfacePropertyIterator.d.h"
#include "BoundingShape.d.h"
#include "CityObjectRelationPropertyIterator.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "ExternalReferenceIterator.d.h"
#include "GenericAttributeKindIterator.d.h"
#include "Id.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"

#include "RoofSurface.d.h"






const Id* ecitygml_RoofSurface_id(const RoofSurface* self);

CodeIterator* ecitygml_RoofSurface_names(const RoofSurface* self);

const BoundingShape* ecitygml_RoofSurface_bounded_by(const RoofSurface* self);

const Id* ecitygml_RoofSurface_feature_id(const RoofSurface* self);

const DateTime* ecitygml_RoofSurface_creation_date(const RoofSurface* self);

const DateTime* ecitygml_RoofSurface_termination_date(const RoofSurface* self);

const DateTime* ecitygml_RoofSurface_valid_from(const RoofSurface* self);

const DateTime* ecitygml_RoofSurface_valid_to(const RoofSurface* self);

typedef struct ecitygml_RoofSurface_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_RoofSurface_relative_to_terrain_result;
ecitygml_RoofSurface_relative_to_terrain_result ecitygml_RoofSurface_relative_to_terrain(const RoofSurface* self);

typedef struct ecitygml_RoofSurface_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_RoofSurface_relative_to_water_result;
ecitygml_RoofSurface_relative_to_water_result ecitygml_RoofSurface_relative_to_water(const RoofSurface* self);

ExternalReferenceIterator* ecitygml_RoofSurface_external_references(const RoofSurface* self);

GenericAttributeKindIterator* ecitygml_RoofSurface_generic_attributes(const RoofSurface* self);

CityObjectRelationPropertyIterator* ecitygml_RoofSurface_related_to(const RoofSurface* self);

const MultiCurveProperty* ecitygml_RoofSurface_lod0_multi_curve(const RoofSurface* self);

const MultiSurfaceProperty* ecitygml_RoofSurface_lod0_multi_surface(const RoofSurface* self);

const MultiSurfaceProperty* ecitygml_RoofSurface_lod1_multi_surface(const RoofSurface* self);

const MultiSurfaceProperty* ecitygml_RoofSurface_lod2_multi_surface(const RoofSurface* self);

const MultiSurfaceProperty* ecitygml_RoofSurface_lod3_multi_surface(const RoofSurface* self);

AbstractFillingSurfacePropertyIterator* ecitygml_RoofSurface_filling_surfaces(const RoofSurface* self);

const RoofSurface* ecitygml_RoofSurface_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_RoofSurface_destroy(RoofSurface* self);





#endif // RoofSurface_H
