#ifndef AbstractFillingSurfacePropertyIterator_H
#define AbstractFillingSurfacePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFillingSurfaceProperty.d.h"

#include "AbstractFillingSurfacePropertyIterator.d.h"






const AbstractFillingSurfaceProperty* ecitygml_AbstractFillingSurfacePropertyIterator_next(AbstractFillingSurfacePropertyIterator* self);

void ecitygml_AbstractFillingSurfacePropertyIterator_destroy(AbstractFillingSurfacePropertyIterator* self);





#endif // AbstractFillingSurfacePropertyIterator_H
