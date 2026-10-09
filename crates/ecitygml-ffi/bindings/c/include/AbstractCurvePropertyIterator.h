#ifndef AbstractCurvePropertyIterator_H
#define AbstractCurvePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCurveProperty.d.h"

#include "AbstractCurvePropertyIterator.d.h"






const AbstractCurveProperty* ecitygml_AbstractCurvePropertyIterator_next(AbstractCurvePropertyIterator* self);

void ecitygml_AbstractCurvePropertyIterator_destroy(AbstractCurvePropertyIterator* self);





#endif // AbstractCurvePropertyIterator_H
