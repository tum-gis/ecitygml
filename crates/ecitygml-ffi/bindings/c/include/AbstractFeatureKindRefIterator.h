#ifndef AbstractFeatureKindRefIterator_H
#define AbstractFeatureKindRefIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AbstractFeatureKindRef.d.h"

#include "AbstractFeatureKindRefIterator.d.h"






AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRefIterator_next(AbstractFeatureKindRefIterator* self);

void ecitygml_AbstractFeatureKindRefIterator_destroy(AbstractFeatureKindRefIterator* self);





#endif // AbstractFeatureKindRefIterator_H
