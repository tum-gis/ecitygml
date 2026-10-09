#ifndef AbstractRingKindIterator_H
#define AbstractRingKindIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractRingKind.d.h"

#include "AbstractRingKindIterator.d.h"






const AbstractRingKind* ecitygml_AbstractRingKindIterator_next(AbstractRingKindIterator* self);

void ecitygml_AbstractRingKindIterator_destroy(AbstractRingKindIterator* self);





#endif // AbstractRingKindIterator_H
