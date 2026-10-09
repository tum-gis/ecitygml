#ifndef Marking_H
#define Marking_H

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
#include "MarkingClassValue.d.h"
#include "MultiCurveProperty.d.h"
#include "MultiSurfaceProperty.d.h"
#include "RelativeToTerrain.d.h"
#include "RelativeToWater.d.h"

#include "Marking.d.h"






const Id* ecitygml_Marking_id(const Marking* self);

CodeIterator* ecitygml_Marking_names(const Marking* self);

const BoundingShape* ecitygml_Marking_bounded_by(const Marking* self);

const Id* ecitygml_Marking_feature_id(const Marking* self);

const DateTime* ecitygml_Marking_creation_date(const Marking* self);

const DateTime* ecitygml_Marking_termination_date(const Marking* self);

const DateTime* ecitygml_Marking_valid_from(const Marking* self);

const DateTime* ecitygml_Marking_valid_to(const Marking* self);

typedef struct ecitygml_Marking_relative_to_terrain_result {union {RelativeToTerrain ok; }; bool is_ok;} ecitygml_Marking_relative_to_terrain_result;
ecitygml_Marking_relative_to_terrain_result ecitygml_Marking_relative_to_terrain(const Marking* self);

typedef struct ecitygml_Marking_relative_to_water_result {union {RelativeToWater ok; }; bool is_ok;} ecitygml_Marking_relative_to_water_result;
ecitygml_Marking_relative_to_water_result ecitygml_Marking_relative_to_water(const Marking* self);

ExternalReferenceIterator* ecitygml_Marking_external_references(const Marking* self);

GenericAttributeKindIterator* ecitygml_Marking_generic_attributes(const Marking* self);

CityObjectRelationPropertyIterator* ecitygml_Marking_related_to(const Marking* self);

const MultiCurveProperty* ecitygml_Marking_lod0_multi_curve(const Marking* self);

const MultiSurfaceProperty* ecitygml_Marking_lod0_multi_surface(const Marking* self);

const MultiSurfaceProperty* ecitygml_Marking_lod1_multi_surface(const Marking* self);

const MultiSurfaceProperty* ecitygml_Marking_lod2_multi_surface(const Marking* self);

const MultiSurfaceProperty* ecitygml_Marking_lod3_multi_surface(const Marking* self);

const Marking* ecitygml_Marking_try_from(const AbstractFeatureKindRef* feature);

const MarkingClassValue* ecitygml_Marking_class(const Marking* self);

void ecitygml_Marking_destroy(Marking* self);





#endif // Marking_H
