#ifndef AbstractCityObjectKindRefIterator_H
#define AbstractCityObjectKindRefIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCityObjectKindRef.d.h"

#include "AbstractCityObjectKindRefIterator.d.h"






AbstractCityObjectKindRef* ecitygml_AbstractCityObjectKindRefIterator_next(AbstractCityObjectKindRefIterator* self);

void ecitygml_AbstractCityObjectKindRefIterator_destroy(AbstractCityObjectKindRefIterator* self);





#endif // AbstractCityObjectKindRefIterator_H
