#ifndef HoleProperty_H
#define HoleProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Hole.d.h"

#include "HoleProperty.d.h"






const Hole* ecitygml_HoleProperty_object(const HoleProperty* self);

const HRef* ecitygml_HoleProperty_href(const HoleProperty* self);

void ecitygml_HoleProperty_destroy(HoleProperty* self);





#endif // HoleProperty_H
