#ifndef AbstractFillingSurfaceProperty_H
#define AbstractFillingSurfaceProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFillingSurfaceKind.d.h"
#include "HRef.d.h"

#include "AbstractFillingSurfaceProperty.d.h"






const AbstractFillingSurfaceKind* ecitygml_AbstractFillingSurfaceProperty_object(const AbstractFillingSurfaceProperty* self);

const HRef* ecitygml_AbstractFillingSurfaceProperty_href(const AbstractFillingSurfaceProperty* self);

void ecitygml_AbstractFillingSurfaceProperty_destroy(AbstractFillingSurfaceProperty* self);





#endif // AbstractFillingSurfaceProperty_H
