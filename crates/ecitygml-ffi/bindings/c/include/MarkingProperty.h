#ifndef MarkingProperty_H
#define MarkingProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "Marking.d.h"

#include "MarkingProperty.d.h"






const Marking* ecitygml_MarkingProperty_object(const MarkingProperty* self);

const HRef* ecitygml_MarkingProperty_href(const MarkingProperty* self);

void ecitygml_MarkingProperty_destroy(MarkingProperty* self);





#endif // MarkingProperty_H
