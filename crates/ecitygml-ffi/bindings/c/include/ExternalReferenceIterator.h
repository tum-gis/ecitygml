#ifndef ExternalReferenceIterator_H
#define ExternalReferenceIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "ExternalReference.d.h"

#include "ExternalReferenceIterator.d.h"






const ExternalReference* ecitygml_ExternalReferenceIterator_next(ExternalReferenceIterator* self);

void ecitygml_ExternalReferenceIterator_destroy(ExternalReferenceIterator* self);





#endif // ExternalReferenceIterator_H
