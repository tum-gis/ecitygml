#ifndef BridgePartProperty_H
#define BridgePartProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BridgePart.d.h"
#include "HRef.d.h"

#include "BridgePartProperty.d.h"






const BridgePart* ecitygml_BridgePartProperty_object(const BridgePartProperty* self);

const HRef* ecitygml_BridgePartProperty_href(const BridgePartProperty* self);

void ecitygml_BridgePartProperty_destroy(BridgePartProperty* self);





#endif // BridgePartProperty_H
