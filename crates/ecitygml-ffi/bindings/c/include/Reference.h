#ifndef Reference_H
#define Reference_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "TrafficSpaceReference.d.h"

#include "Reference.d.h"






Reference* ecitygml_Reference_from_traffic_space_reference(const TrafficSpaceReference* reference);

const HRef* ecitygml_Reference_href(const Reference* self);

void ecitygml_Reference_destroy(Reference* self);





#endif // Reference_H
