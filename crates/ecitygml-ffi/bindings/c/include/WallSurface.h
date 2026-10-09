#ifndef WallSurface_H
#define WallSurface_H

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

#include "WallSurface.d.h"






const Id* ecitygml_WallSurface_id(const WallSurface* self);

CodeIterator* ecitygml_WallSurface_names(const WallSurface* self);

const BoundingShape* ecitygml_WallSurface_bounded_by(const WallSurface* self);

const Id* ecitygml_WallSurface_feature_id(const WallSurface* self);

const DateTime* ecitygml_WallSurface_creation_date(const WallSurface* self);

const DateTime* ecitygml_WallSurface_termination_date(const WallSurface* self);

const DateTime* ecitygml_WallSurface_valid_from(const WallSurface* self);

const DateTime* ecitygml_WallSurface_valid_to(const WallSurface* self);

typedef struct ecitygml_WallSurface_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_WallSurface_relative_to_terrain_result;
ecitygml_WallSurface_relative_to_terrain_result ecitygml_WallSurface_relative_to_terrain(const WallSurface* self);

typedef struct ecitygml_WallSurface_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_WallSurface_relative_to_water_result;
ecitygml_WallSurface_relative_to_water_result ecitygml_WallSurface_relative_to_water(const WallSurface* self);

ExternalReferenceIterator* ecitygml_WallSurface_external_references(const WallSurface* self);

GenericAttributeKindIterator* ecitygml_WallSurface_generic_attributes(const WallSurface* self);

CityObjectRelationPropertyIterator* ecitygml_WallSurface_related_to(const WallSurface* self);

const MultiCurveProperty* ecitygml_WallSurface_lod0_multi_curve(const WallSurface* self);

const MultiSurfaceProperty* ecitygml_WallSurface_lod0_multi_surface(const WallSurface* self);

const MultiSurfaceProperty* ecitygml_WallSurface_lod1_multi_surface(const WallSurface* self);

const MultiSurfaceProperty* ecitygml_WallSurface_lod2_multi_surface(const WallSurface* self);

const MultiSurfaceProperty* ecitygml_WallSurface_lod3_multi_surface(const WallSurface* self);

AbstractFillingSurfacePropertyIterator* ecitygml_WallSurface_filling_surfaces(const WallSurface* self);

const WallSurface* ecitygml_WallSurface_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_WallSurface_destroy(WallSurface* self);





#endif // WallSurface_H
