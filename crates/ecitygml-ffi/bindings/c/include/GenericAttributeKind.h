#ifndef GenericAttributeKind_H
#define GenericAttributeKind_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "DoubleAttribute.d.h"
#include "IntAttribute.d.h"
#include "StringAttribute.d.h"

#include "GenericAttributeKind.d.h"






DiplomatStringView ecitygml_GenericAttributeKind_name(const GenericAttributeKind* self);

const StringAttribute* ecitygml_GenericAttributeKind_as_string(const GenericAttributeKind* self);

const IntAttribute* ecitygml_GenericAttributeKind_as_int(const GenericAttributeKind* self);

const DoubleAttribute* ecitygml_GenericAttributeKind_as_double(const GenericAttributeKind* self);

void ecitygml_GenericAttributeKind_destroy(GenericAttributeKind* self);





#endif // GenericAttributeKind_H
