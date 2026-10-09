#ifndef AbstractSpaceBoundaryPropertyIterator_H
#define AbstractSpaceBoundaryPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSpaceBoundaryProperty.d.h"

#include "AbstractSpaceBoundaryPropertyIterator.d.h"






const AbstractSpaceBoundaryProperty* ecitygml_AbstractSpaceBoundaryPropertyIterator_next(AbstractSpaceBoundaryPropertyIterator* self);

void ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(AbstractSpaceBoundaryPropertyIterator* self);





#endif // AbstractSpaceBoundaryPropertyIterator_H
