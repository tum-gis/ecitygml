#ifndef GenericAttributeKindIterator_H
#define GenericAttributeKindIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "GenericAttributeKind.d.h"

#include "GenericAttributeKindIterator.d.h"






const GenericAttributeKind* ecitygml_GenericAttributeKindIterator_next(GenericAttributeKindIterator* self);

void ecitygml_GenericAttributeKindIterator_destroy(GenericAttributeKindIterator* self);





#endif // GenericAttributeKindIterator_H
