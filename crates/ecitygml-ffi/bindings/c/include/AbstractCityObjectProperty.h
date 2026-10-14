#ifndef AbstractCityObjectProperty_H
#define AbstractCityObjectProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectKind.d.h"
#include "HRef.d.h"

#include "AbstractCityObjectProperty.d.h"






const AbstractCityObjectKind* ecitygml_AbstractCityObjectProperty_object(const AbstractCityObjectProperty* self);

const HRef* ecitygml_AbstractCityObjectProperty_href(const AbstractCityObjectProperty* self);

void ecitygml_AbstractCityObjectProperty_destroy(AbstractCityObjectProperty* self);





#endif // AbstractCityObjectProperty_H
