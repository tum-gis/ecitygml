#ifndef TrafficSpaceProperty_H
#define TrafficSpaceProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "TrafficSpace.d.h"

#include "TrafficSpaceProperty.d.h"






const TrafficSpace* ecitygml_TrafficSpaceProperty_object(const TrafficSpaceProperty* self);

const HRef* ecitygml_TrafficSpaceProperty_href(const TrafficSpaceProperty* self);

void ecitygml_TrafficSpaceProperty_destroy(TrafficSpaceProperty* self);





#endif // TrafficSpaceProperty_H
