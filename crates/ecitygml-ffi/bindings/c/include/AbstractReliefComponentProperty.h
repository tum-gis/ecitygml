#ifndef AbstractReliefComponentProperty_H
#define AbstractReliefComponentProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractReliefComponentKind.d.h"
#include "HRef.d.h"

#include "AbstractReliefComponentProperty.d.h"






const AbstractReliefComponentKind* ecitygml_AbstractReliefComponentProperty_object(const AbstractReliefComponentProperty* self);

const HRef* ecitygml_AbstractReliefComponentProperty_href(const AbstractReliefComponentProperty* self);

void ecitygml_AbstractReliefComponentProperty_destroy(AbstractReliefComponentProperty* self);





#endif // AbstractReliefComponentProperty_H
