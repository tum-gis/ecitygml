#ifndef TrafficSpaceReferenceIterator_H
#define TrafficSpaceReferenceIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficSpaceReference.d.h"

#include "TrafficSpaceReferenceIterator.d.h"






const TrafficSpaceReference* ecitygml_TrafficSpaceReferenceIterator_next(TrafficSpaceReferenceIterator* self);

void ecitygml_TrafficSpaceReferenceIterator_destroy(TrafficSpaceReferenceIterator* self);





#endif // TrafficSpaceReferenceIterator_H
