#ifndef IntersectionProperty_H
#define IntersectionProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Intersection.d.h"

#include "IntersectionProperty.d.h"






const Intersection* ecitygml_IntersectionProperty_object(const IntersectionProperty* self);

const HRef* ecitygml_IntersectionProperty_href(const IntersectionProperty* self);

void ecitygml_IntersectionProperty_destroy(IntersectionProperty* self);





#endif // IntersectionProperty_H
