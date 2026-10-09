#ifndef IntersectionPropertyIterator_H
#define IntersectionPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "IntersectionProperty.d.h"

#include "IntersectionPropertyIterator.d.h"






const IntersectionProperty* ecitygml_IntersectionPropertyIterator_next(IntersectionPropertyIterator* self);

void ecitygml_IntersectionPropertyIterator_destroy(IntersectionPropertyIterator* self);





#endif // IntersectionPropertyIterator_H
