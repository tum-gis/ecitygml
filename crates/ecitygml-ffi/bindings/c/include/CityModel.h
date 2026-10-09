#ifndef CityModel_H
#define CityModel_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectKindRefIterator.d.h"
#include "AbstractFeatureKindRefIterator.d.h"
#include "BoundingShape.d.h"
#include "CodeIterator.d.h"
#include "DateTime.d.h"
#include "Id.d.h"

#include "CityModel.d.h"






const Id* ecitygml_CityModel_id(const CityModel* self);

CodeIterator* ecitygml_CityModel_names(const CityModel* self);

const BoundingShape* ecitygml_CityModel_bounded_by(const CityModel* self);

const Id* ecitygml_CityModel_feature_id(const CityModel* self);

const DateTime* ecitygml_CityModel_creation_date(const CityModel* self);

const DateTime* ecitygml_CityModel_termination_date(const CityModel* self);

const DateTime* ecitygml_CityModel_valid_from(const CityModel* self);

const DateTime* ecitygml_CityModel_valid_to(const CityModel* self);

AbstractFeatureKindRefIterator* ecitygml_CityModel_iter_features(const CityModel* self);

AbstractCityObjectKindRefIterator* ecitygml_CityModel_iter_city_objects(const CityModel* self);

void ecitygml_CityModel_recompute_child_bounding_shapes(CityModel* self);

size_t ecitygml_CityModel_city_objects_len(const CityModel* self);

void ecitygml_CityModel_destroy(CityModel* self);





#endif // CityModel_H
