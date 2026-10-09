#ifndef GenericAttributeSet_H
#define GenericAttributeSet_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "GenericAttributeKind.d.h"
#include "GenericAttributeKindIterator.d.h"

#include "GenericAttributeSet.d.h"






const GenericAttributeSet* ecitygml_GenericAttributeSet_try_from(const GenericAttributeKind* attribute);

DiplomatStringView ecitygml_GenericAttributeSet_name(const GenericAttributeSet* self);

GenericAttributeKindIterator* ecitygml_GenericAttributeSet_generic_attributes(const GenericAttributeSet* self);

void ecitygml_GenericAttributeSet_destroy(GenericAttributeSet* self);





#endif // GenericAttributeSet_H
