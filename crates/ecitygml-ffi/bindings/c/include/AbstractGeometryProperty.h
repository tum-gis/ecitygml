#ifndef AbstractGeometryProperty_H
#define AbstractGeometryProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractGeometryKind.d.h"
#include "HRef.d.h"

#include "AbstractGeometryProperty.d.h"






const AbstractGeometryKind* ecitygml_AbstractGeometryProperty_object(const AbstractGeometryProperty* self);

const HRef* ecitygml_AbstractGeometryProperty_href(const AbstractGeometryProperty* self);

void ecitygml_AbstractGeometryProperty_destroy(AbstractGeometryProperty* self);





#endif // AbstractGeometryProperty_H
