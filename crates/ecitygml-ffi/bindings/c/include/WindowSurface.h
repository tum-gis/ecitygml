#ifndef WindowSurface_H
#define WindowSurface_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
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

#include "WindowSurface.d.h"






const Id* ecitygml_WindowSurface_id(const WindowSurface* self);

CodeIterator* ecitygml_WindowSurface_names(const WindowSurface* self);

const BoundingShape* ecitygml_WindowSurface_bounded_by(const WindowSurface* self);

const Id* ecitygml_WindowSurface_feature_id(const WindowSurface* self);

const DateTime* ecitygml_WindowSurface_creation_date(const WindowSurface* self);

const DateTime* ecitygml_WindowSurface_termination_date(const WindowSurface* self);

const DateTime* ecitygml_WindowSurface_valid_from(const WindowSurface* self);

const DateTime* ecitygml_WindowSurface_valid_to(const WindowSurface* self);

typedef struct ecitygml_WindowSurface_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_WindowSurface_relative_to_terrain_result;
ecitygml_WindowSurface_relative_to_terrain_result ecitygml_WindowSurface_relative_to_terrain(const WindowSurface* self);

typedef struct ecitygml_WindowSurface_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_WindowSurface_relative_to_water_result;
ecitygml_WindowSurface_relative_to_water_result ecitygml_WindowSurface_relative_to_water(const WindowSurface* self);

ExternalReferenceIterator* ecitygml_WindowSurface_external_references(const WindowSurface* self);

GenericAttributeKindIterator* ecitygml_WindowSurface_generic_attributes(const WindowSurface* self);

CityObjectRelationPropertyIterator* ecitygml_WindowSurface_related_to(const WindowSurface* self);

const MultiCurveProperty* ecitygml_WindowSurface_lod0_multi_curve(const WindowSurface* self);

const MultiSurfaceProperty* ecitygml_WindowSurface_lod0_multi_surface(const WindowSurface* self);

const MultiSurfaceProperty* ecitygml_WindowSurface_lod1_multi_surface(const WindowSurface* self);

const MultiSurfaceProperty* ecitygml_WindowSurface_lod2_multi_surface(const WindowSurface* self);

const MultiSurfaceProperty* ecitygml_WindowSurface_lod3_multi_surface(const WindowSurface* self);

const WindowSurface* ecitygml_WindowSurface_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_WindowSurface_destroy(WindowSurface* self);





#endif // WindowSurface_H
