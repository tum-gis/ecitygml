#ifndef AuxiliaryTrafficArea_H
#define AuxiliaryTrafficArea_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"
#include "AuxiliaryTrafficAreaClassValue.d.h"
#include "AuxiliaryTrafficAreaFunctionValueIterator.d.h"
#include "AuxiliaryTrafficAreaUsageValueIterator.d.h"
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

#include "AuxiliaryTrafficArea.d.h"






const Id* ecitygml_AuxiliaryTrafficArea_id(const AuxiliaryTrafficArea* self);

CodeIterator* ecitygml_AuxiliaryTrafficArea_names(const AuxiliaryTrafficArea* self);

const BoundingShape* ecitygml_AuxiliaryTrafficArea_bounded_by(const AuxiliaryTrafficArea* self);

const Id* ecitygml_AuxiliaryTrafficArea_feature_id(const AuxiliaryTrafficArea* self);

const DateTime* ecitygml_AuxiliaryTrafficArea_creation_date(const AuxiliaryTrafficArea* self);

const DateTime* ecitygml_AuxiliaryTrafficArea_termination_date(const AuxiliaryTrafficArea* self);

const DateTime* ecitygml_AuxiliaryTrafficArea_valid_from(const AuxiliaryTrafficArea* self);

const DateTime* ecitygml_AuxiliaryTrafficArea_valid_to(const AuxiliaryTrafficArea* self);

typedef struct ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result;
ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result ecitygml_AuxiliaryTrafficArea_relative_to_terrain(const AuxiliaryTrafficArea* self);

typedef struct ecitygml_AuxiliaryTrafficArea_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficArea_relative_to_water_result;
ecitygml_AuxiliaryTrafficArea_relative_to_water_result ecitygml_AuxiliaryTrafficArea_relative_to_water(const AuxiliaryTrafficArea* self);

ExternalReferenceIterator* ecitygml_AuxiliaryTrafficArea_external_references(const AuxiliaryTrafficArea* self);

GenericAttributeKindIterator* ecitygml_AuxiliaryTrafficArea_generic_attributes(const AuxiliaryTrafficArea* self);

CityObjectRelationPropertyIterator* ecitygml_AuxiliaryTrafficArea_related_to(const AuxiliaryTrafficArea* self);

const MultiCurveProperty* ecitygml_AuxiliaryTrafficArea_lod0_multi_curve(const AuxiliaryTrafficArea* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod0_multi_surface(const AuxiliaryTrafficArea* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod1_multi_surface(const AuxiliaryTrafficArea* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(const AuxiliaryTrafficArea* self);

const MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod3_multi_surface(const AuxiliaryTrafficArea* self);

const AuxiliaryTrafficArea* ecitygml_AuxiliaryTrafficArea_try_from(const AbstractFeatureKindRef* feature);

const AuxiliaryTrafficAreaClassValue* ecitygml_AuxiliaryTrafficArea_class(const AuxiliaryTrafficArea* self);

AuxiliaryTrafficAreaFunctionValueIterator* ecitygml_AuxiliaryTrafficArea_functions(const AuxiliaryTrafficArea* self);

AuxiliaryTrafficAreaUsageValueIterator* ecitygml_AuxiliaryTrafficArea_usages(const AuxiliaryTrafficArea* self);

const SurfaceMaterialValue* ecitygml_AuxiliaryTrafficArea_surface_material(const AuxiliaryTrafficArea* self);

void ecitygml_AuxiliaryTrafficArea_destroy(AuxiliaryTrafficArea* self);





#endif // AuxiliaryTrafficArea_H
