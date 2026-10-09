#ifndef HeightIterator_H
#define HeightIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Height.d.h"

#include "HeightIterator.d.h"






const Height* ecitygml_HeightIterator_next(HeightIterator* self);

void ecitygml_HeightIterator_destroy(HeightIterator* self);





#endif // HeightIterator_H
