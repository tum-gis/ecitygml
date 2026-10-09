#ifndef AbstractSpaceBoundaryProperty_H
#define AbstractSpaceBoundaryProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSpaceBoundaryKind.d.h"
#include "HRef.d.h"

#include "AbstractSpaceBoundaryProperty.d.h"






const AbstractSpaceBoundaryKind* ecitygml_AbstractSpaceBoundaryProperty_object(const AbstractSpaceBoundaryProperty* self);

const HRef* ecitygml_AbstractSpaceBoundaryProperty_href(const AbstractSpaceBoundaryProperty* self);

void ecitygml_AbstractSpaceBoundaryProperty_destroy(AbstractSpaceBoundaryProperty* self);





#endif // AbstractSpaceBoundaryProperty_H
