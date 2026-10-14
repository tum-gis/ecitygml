#ifndef AbstractCityObjectPropertyIterator_H
#define AbstractCityObjectPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectProperty.d.h"

#include "AbstractCityObjectPropertyIterator.d.h"






const AbstractCityObjectProperty* ecitygml_AbstractCityObjectPropertyIterator_next(AbstractCityObjectPropertyIterator* self);

void ecitygml_AbstractCityObjectPropertyIterator_destroy(AbstractCityObjectPropertyIterator* self);





#endif // AbstractCityObjectPropertyIterator_H
