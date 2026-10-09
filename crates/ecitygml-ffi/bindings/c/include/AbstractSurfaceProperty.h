#ifndef AbstractSurfaceProperty_H
#define AbstractSurfaceProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfaceKind.d.h"
#include "HRef.d.h"

#include "AbstractSurfaceProperty.d.h"






const AbstractSurfaceKind* ecitygml_AbstractSurfaceProperty_object(const AbstractSurfaceProperty* self);

const HRef* ecitygml_AbstractSurfaceProperty_href(const AbstractSurfaceProperty* self);

void ecitygml_AbstractSurfaceProperty_destroy(AbstractSurfaceProperty* self);





#endif // AbstractSurfaceProperty_H
