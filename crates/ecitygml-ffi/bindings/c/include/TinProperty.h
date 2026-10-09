#ifndef TinProperty_H
#define TinProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "TriangulatedSurface.d.h"

#include "TinProperty.d.h"






const TriangulatedSurface* ecitygml_TinProperty_object(const TinProperty* self);

const HRef* ecitygml_TinProperty_href(const TinProperty* self);

void ecitygml_TinProperty_destroy(TinProperty* self);





#endif // TinProperty_H
