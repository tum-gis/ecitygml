#ifndef SectionPropertyIterator_H
#define SectionPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "SectionProperty.d.h"

#include "SectionPropertyIterator.d.h"






const SectionProperty* ecitygml_SectionPropertyIterator_next(SectionPropertyIterator* self);

void ecitygml_SectionPropertyIterator_destroy(SectionPropertyIterator* self);





#endif // SectionPropertyIterator_H
