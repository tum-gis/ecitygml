#ifndef DoorSurface_H
#define DoorSurface_H

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

#include "DoorSurface.d.h"






const Id* ecitygml_DoorSurface_id(const DoorSurface* self);

CodeIterator* ecitygml_DoorSurface_names(const DoorSurface* self);

const BoundingShape* ecitygml_DoorSurface_bounded_by(const DoorSurface* self);

const Id* ecitygml_DoorSurface_feature_id(const DoorSurface* self);

const DateTime* ecitygml_DoorSurface_creation_date(const DoorSurface* self);

const DateTime* ecitygml_DoorSurface_termination_date(const DoorSurface* self);

const DateTime* ecitygml_DoorSurface_valid_from(const DoorSurface* self);

const DateTime* ecitygml_DoorSurface_valid_to(const DoorSurface* self);

typedef struct ecitygml_DoorSurface_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_DoorSurface_relative_to_terrain_result;
ecitygml_DoorSurface_relative_to_terrain_result ecitygml_DoorSurface_relative_to_terrain(const DoorSurface* self);

typedef struct ecitygml_DoorSurface_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_DoorSurface_relative_to_water_result;
ecitygml_DoorSurface_relative_to_water_result ecitygml_DoorSurface_relative_to_water(const DoorSurface* self);

ExternalReferenceIterator* ecitygml_DoorSurface_external_references(const DoorSurface* self);

GenericAttributeKindIterator* ecitygml_DoorSurface_generic_attributes(const DoorSurface* self);

CityObjectRelationPropertyIterator* ecitygml_DoorSurface_related_to(const DoorSurface* self);

const MultiCurveProperty* ecitygml_DoorSurface_lod0_multi_curve(const DoorSurface* self);

const MultiSurfaceProperty* ecitygml_DoorSurface_lod0_multi_surface(const DoorSurface* self);

const MultiSurfaceProperty* ecitygml_DoorSurface_lod1_multi_surface(const DoorSurface* self);

const MultiSurfaceProperty* ecitygml_DoorSurface_lod2_multi_surface(const DoorSurface* self);

const MultiSurfaceProperty* ecitygml_DoorSurface_lod3_multi_surface(const DoorSurface* self);

const DoorSurface* ecitygml_DoorSurface_try_from(const AbstractFeatureKindRef* feature);

void ecitygml_DoorSurface_destroy(DoorSurface* self);





#endif // DoorSurface_H
