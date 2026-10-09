#ifndef AbstractSurfacePatchKindIterator_H
#define AbstractSurfacePatchKindIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractSurfacePatchKind.d.h"

#include "AbstractSurfacePatchKindIterator.d.h"






const AbstractSurfacePatchKind* ecitygml_AbstractSurfacePatchKindIterator_next(AbstractSurfacePatchKindIterator* self);

void ecitygml_AbstractSurfacePatchKindIterator_destroy(AbstractSurfacePatchKindIterator* self);





#endif // AbstractSurfacePatchKindIterator_H
