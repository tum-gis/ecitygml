#ifndef MarkingPropertyIterator_H
#define MarkingPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "MarkingProperty.d.h"

#include "MarkingPropertyIterator.d.h"






const MarkingProperty* ecitygml_MarkingPropertyIterator_next(MarkingPropertyIterator* self);

void ecitygml_MarkingPropertyIterator_destroy(MarkingPropertyIterator* self);





#endif // MarkingPropertyIterator_H
