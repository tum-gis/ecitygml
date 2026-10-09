#ifndef TrafficArea_H
#define TrafficArea_H

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
#include "SurfaceMaterialValue.d.h"
#include "TrafficAreaClassValue.d.h"
#include "TrafficAreaFunctionValueIterator.d.h"
#include "TrafficAreaUsageValueIterator.d.h"

#include "TrafficArea.d.h"






const Id* ecitygml_TrafficArea_id(const TrafficArea* self);

CodeIterator* ecitygml_TrafficArea_names(const TrafficArea* self);

const BoundingShape* ecitygml_TrafficArea_bounded_by(const TrafficArea* self);

const Id* ecitygml_TrafficArea_feature_id(const TrafficArea* self);

const DateTime* ecitygml_TrafficArea_creation_date(const TrafficArea* self);

const DateTime* ecitygml_TrafficArea_termination_date(const TrafficArea* self);

const DateTime* ecitygml_TrafficArea_valid_from(const TrafficArea* self);

const DateTime* ecitygml_TrafficArea_valid_to(const TrafficArea* self);

typedef struct ecitygml_TrafficArea_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_TrafficArea_relative_to_terrain_result;
ecitygml_TrafficArea_relative_to_terrain_result ecitygml_TrafficArea_relative_to_terrain(const TrafficArea* self);

typedef struct ecitygml_TrafficArea_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_TrafficArea_relative_to_water_result;
ecitygml_TrafficArea_relative_to_water_result ecitygml_TrafficArea_relative_to_water(const TrafficArea* self);

ExternalReferenceIterator* ecitygml_TrafficArea_external_references(const TrafficArea* self);

GenericAttributeKindIterator* ecitygml_TrafficArea_generic_attributes(const TrafficArea* self);

CityObjectRelationPropertyIterator* ecitygml_TrafficArea_related_to(const TrafficArea* self);

const MultiCurveProperty* ecitygml_TrafficArea_lod0_multi_curve(const TrafficArea* self);

const MultiSurfaceProperty* ecitygml_TrafficArea_lod0_multi_surface(const TrafficArea* self);

const MultiSurfaceProperty* ecitygml_TrafficArea_lod1_multi_surface(const TrafficArea* self);

const MultiSurfaceProperty* ecitygml_TrafficArea_lod2_multi_surface(const TrafficArea* self);

const MultiSurfaceProperty* ecitygml_TrafficArea_lod3_multi_surface(const TrafficArea* self);

const TrafficArea* ecitygml_TrafficArea_try_from(const AbstractFeatureKindRef* feature);

const TrafficAreaClassValue* ecitygml_TrafficArea_class(const TrafficArea* self);

TrafficAreaFunctionValueIterator* ecitygml_TrafficArea_functions(const TrafficArea* self);

TrafficAreaUsageValueIterator* ecitygml_TrafficArea_usages(const TrafficArea* self);

const SurfaceMaterialValue* ecitygml_TrafficArea_surface_material(const TrafficArea* self);

void ecitygml_TrafficArea_destroy(TrafficArea* self);





#endif // TrafficArea_H
