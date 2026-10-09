#ifndef AbstractCurveProperty_H
#define AbstractCurveProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractCurveKind.d.h"
#include "HRef.d.h"

#include "AbstractCurveProperty.d.h"






const AbstractCurveKind* ecitygml_AbstractCurveProperty_object(const AbstractCurveProperty* self);

const HRef* ecitygml_AbstractCurveProperty_href(const AbstractCurveProperty* self);

void ecitygml_AbstractCurveProperty_destroy(AbstractCurveProperty* self);





#endif // AbstractCurveProperty_H
