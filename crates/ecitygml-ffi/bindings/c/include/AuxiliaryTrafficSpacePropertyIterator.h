#ifndef AuxiliaryTrafficSpacePropertyIterator_H
#define AuxiliaryTrafficSpacePropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficSpaceProperty.d.h"

#include "AuxiliaryTrafficSpacePropertyIterator.d.h"






const AuxiliaryTrafficSpaceProperty* ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(AuxiliaryTrafficSpacePropertyIterator* self);

void ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(AuxiliaryTrafficSpacePropertyIterator* self);





#endif // AuxiliaryTrafficSpacePropertyIterator_H
