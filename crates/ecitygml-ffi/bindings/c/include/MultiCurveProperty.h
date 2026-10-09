#ifndef MultiCurveProperty_H
#define MultiCurveProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "MultiCurve.d.h"

#include "MultiCurveProperty.d.h"






const MultiCurve* ecitygml_MultiCurveProperty_object(const MultiCurveProperty* self);

const HRef* ecitygml_MultiCurveProperty_href(const MultiCurveProperty* self);

void ecitygml_MultiCurveProperty_destroy(MultiCurveProperty* self);





#endif // MultiCurveProperty_H
