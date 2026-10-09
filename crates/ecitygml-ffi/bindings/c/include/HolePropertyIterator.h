#ifndef HolePropertyIterator_H
#define HolePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HoleProperty.d.h"

#include "HolePropertyIterator.d.h"






const HoleProperty* ecitygml_HolePropertyIterator_next(HolePropertyIterator* self);

void ecitygml_HolePropertyIterator_destroy(HolePropertyIterator* self);





#endif // HolePropertyIterator_H
