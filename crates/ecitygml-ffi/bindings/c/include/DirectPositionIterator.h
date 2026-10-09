#ifndef DirectPositionIterator_H
#define DirectPositionIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "DirectPosition.d.h"

#include "DirectPositionIterator.d.h"






const DirectPosition* ecitygml_DirectPositionIterator_next(DirectPositionIterator* self);

void ecitygml_DirectPositionIterator_destroy(DirectPositionIterator* self);





#endif // DirectPositionIterator_H
