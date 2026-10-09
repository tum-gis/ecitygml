#ifndef TrafficSpacePropertyIterator_H
#define TrafficSpacePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficSpaceProperty.d.h"

#include "TrafficSpacePropertyIterator.d.h"






const TrafficSpaceProperty* ecitygml_TrafficSpacePropertyIterator_next(TrafficSpacePropertyIterator* self);

void ecitygml_TrafficSpacePropertyIterator_destroy(TrafficSpacePropertyIterator* self);





#endif // TrafficSpacePropertyIterator_H
