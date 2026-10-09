#ifndef ImplicitGeometryProperty_H
#define ImplicitGeometryProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "ImplicitGeometry.d.h"

#include "ImplicitGeometryProperty.d.h"






const ImplicitGeometry* ecitygml_ImplicitGeometryProperty_object(const ImplicitGeometryProperty* self);

const HRef* ecitygml_ImplicitGeometryProperty_href(const ImplicitGeometryProperty* self);

void ecitygml_ImplicitGeometryProperty_destroy(ImplicitGeometryProperty* self);





#endif // ImplicitGeometryProperty_H
