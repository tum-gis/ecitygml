#ifndef AbstractSurfacePropertyIterator_H
#define AbstractSurfacePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfaceProperty.d.h"

#include "AbstractSurfacePropertyIterator.d.h"






const AbstractSurfaceProperty* ecitygml_AbstractSurfacePropertyIterator_next(AbstractSurfacePropertyIterator* self);

void ecitygml_AbstractSurfacePropertyIterator_destroy(AbstractSurfacePropertyIterator* self);





#endif // AbstractSurfacePropertyIterator_H
