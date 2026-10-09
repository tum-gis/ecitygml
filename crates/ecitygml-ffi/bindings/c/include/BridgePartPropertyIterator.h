#ifndef BridgePartPropertyIterator_H
#define BridgePartPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BridgePartProperty.d.h"

#include "BridgePartPropertyIterator.d.h"






const BridgePartProperty* ecitygml_BridgePartPropertyIterator_next(BridgePartPropertyIterator* self);

void ecitygml_BridgePartPropertyIterator_destroy(BridgePartPropertyIterator* self);





#endif // BridgePartPropertyIterator_H
