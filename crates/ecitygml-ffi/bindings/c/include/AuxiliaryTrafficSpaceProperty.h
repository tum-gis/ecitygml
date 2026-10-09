#ifndef AuxiliaryTrafficSpaceProperty_H
#define AuxiliaryTrafficSpaceProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "AuxiliaryTrafficSpace.d.h"
#include "HRef.d.h"

#include "AuxiliaryTrafficSpaceProperty.d.h"






const AuxiliaryTrafficSpace* ecitygml_AuxiliaryTrafficSpaceProperty_object(const AuxiliaryTrafficSpaceProperty* self);

const HRef* ecitygml_AuxiliaryTrafficSpaceProperty_href(const AuxiliaryTrafficSpaceProperty* self);

void ecitygml_AuxiliaryTrafficSpaceProperty_destroy(AuxiliaryTrafficSpaceProperty* self);





#endif // AuxiliaryTrafficSpaceProperty_H
