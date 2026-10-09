#ifndef TunnelPartPropertyIterator_H
#define TunnelPartPropertyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TunnelPartProperty.d.h"

#include "TunnelPartPropertyIterator.d.h"






const TunnelPartProperty* ecitygml_TunnelPartPropertyIterator_next(TunnelPartPropertyIterator* self);

void ecitygml_TunnelPartPropertyIterator_destroy(TunnelPartPropertyIterator* self);





#endif // TunnelPartPropertyIterator_H
