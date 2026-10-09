#ifndef BoundingShape_H
#define BoundingShape_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Envelope.d.h"

#include "BoundingShape.d.h"






const Envelope* ecitygml_BoundingShape_envelope(const BoundingShape* self);

void ecitygml_BoundingShape_destroy(BoundingShape* self);





#endif // BoundingShape_H
