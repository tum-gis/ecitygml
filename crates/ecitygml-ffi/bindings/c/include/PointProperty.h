#ifndef PointProperty_H
#define PointProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Point.d.h"

#include "PointProperty.d.h"






const Point* ecitygml_PointProperty_object(const PointProperty* self);

const HRef* ecitygml_PointProperty_href(const PointProperty* self);

void ecitygml_PointProperty_destroy(PointProperty* self);





#endif // PointProperty_H
