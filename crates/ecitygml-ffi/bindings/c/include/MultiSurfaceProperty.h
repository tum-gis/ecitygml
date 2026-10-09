#ifndef MultiSurfaceProperty_H
#define MultiSurfaceProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "MultiSurface.d.h"

#include "MultiSurfaceProperty.d.h"






const MultiSurface* ecitygml_MultiSurfaceProperty_object(const MultiSurfaceProperty* self);

const HRef* ecitygml_MultiSurfaceProperty_href(const MultiSurfaceProperty* self);

void ecitygml_MultiSurfaceProperty_destroy(MultiSurfaceProperty* self);





#endif // MultiSurfaceProperty_H
