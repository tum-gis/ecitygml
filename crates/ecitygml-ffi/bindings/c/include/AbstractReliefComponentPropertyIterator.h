#ifndef AbstractReliefComponentPropertyIterator_H
#define AbstractReliefComponentPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractReliefComponentProperty.d.h"

#include "AbstractReliefComponentPropertyIterator.d.h"






const AbstractReliefComponentProperty* ecitygml_AbstractReliefComponentPropertyIterator_next(AbstractReliefComponentPropertyIterator* self);

void ecitygml_AbstractReliefComponentPropertyIterator_destroy(AbstractReliefComponentPropertyIterator* self);





#endif // AbstractReliefComponentPropertyIterator_H
