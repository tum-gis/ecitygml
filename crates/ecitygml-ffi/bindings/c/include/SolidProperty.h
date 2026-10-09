#ifndef SolidProperty_H
#define SolidProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Solid.d.h"

#include "SolidProperty.d.h"






const Solid* ecitygml_SolidProperty_object(const SolidProperty* self);

const HRef* ecitygml_SolidProperty_href(const SolidProperty* self);

void ecitygml_SolidProperty_destroy(SolidProperty* self);





#endif // SolidProperty_H
