#ifndef Reference_H
#define Reference_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"

#include "Reference.d.h"






const HRef* ecitygml_Reference_href(const Reference* self);

void ecitygml_Reference_destroy(Reference* self);





#endif // Reference_H
