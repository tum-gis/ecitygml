#ifndef GroundSurface_H
#define GroundSurface_H

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

#include "GroundSurface.d.h"






const Id* ecitygml_GroundSurface_id(const GroundSurface* self);

CodeIterator* ecitygml_GroundSurface_names(const GroundSurface* self);

const BoundingShape* ecitygml_GroundSurface_bounded_by(const GroundSurface* self);

const Id* ecitygml_GroundSurface_feature_id(const GroundSurface* self);

const DateTime* ecitygml_GroundSurface_creation_date(const GroundSurface* self);

const DateTime* ecitygml_GroundSurface_termination_date(const GroundSurface* self);

const DateTime* ecitygml_GroundSurface_valid_from(const GroundSurface* self);

const DateTime* ecitygml_GroundSurface_valid_to(const GroundSurface* self);

typedef struct ecitygml_GroundSurface_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_GroundSurface_relative_to_terrain_result;
ecitygml_GroundSurface_relative_to_terrain_result ecitygml_GroundSurface_relative_to_terrain(const GroundSurface* self);

typedef struct ecitygml_GroundSurface_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_GroundSurface_relative_to_water_result;
ecitygml_GroundSurface_relative_to_water_result ecitygml_GroundSurface_relative_to_water(const GroundSurface* self);

ExternalReferenceIterator* ecitygml_GroundSurface_external_references(const GroundSurface* self);

GenericAttributeKindIterator* ecitygml_GroundSurface_generic_attributes(const GroundSurface* self);

CityObjectRelationPropertyIterator* ecitygml_GroundSurface_related_to(const GroundSurface* self);

const MultiCurveProperty* ecitygml_GroundSurface_lod0_multi_curve(const GroundSurface* self);

const MultiSurfaceProperty* ecitygml_GroundSurface_lod0_multi_surface(const GroundSurface* self);

const MultiSurfaceProperty* ecitygml_GroundSurface_lod1_multi_surface(const GroundSurface* self);

const MultiSurfaceProperty* ecitygml_GroundSurface_lod2_multi_surface(const GroundSurface* self);

const MultiSurfaceProperty* ecitygml_GroundSurface_lod3_multi_surface(const GroundSurface* self);

AbstractFillingSurfacePropertyIterator* ecitygml_GroundSurface_filling_surfaces(const GroundSurface* self);

const GroundSurface* ecitygml_GroundSurface_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_GroundSurface_destroy(GroundSurface* self);





#endif // GroundSurface_H
