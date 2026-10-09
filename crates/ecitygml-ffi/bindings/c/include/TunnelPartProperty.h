#ifndef TunnelPartProperty_H
#define TunnelPartProperty_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "HRef.d.h"
#include "TunnelPart.d.h"

#include "TunnelPartProperty.d.h"






const TunnelPart* ecitygml_TunnelPartProperty_object(const TunnelPartProperty* self);

const HRef* ecitygml_TunnelPartProperty_href(const TunnelPartProperty* self);

void ecitygml_TunnelPartProperty_destroy(TunnelPartProperty* self);





#endif // TunnelPartProperty_H
