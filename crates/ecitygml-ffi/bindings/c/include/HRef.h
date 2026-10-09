#ifndef HRef_H
#define HRef_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "HRef.d.h"






typedef struct ecitygml_HRef_local_id_result {union {DiplomatStringView ok; }; bool is_ok;} ecitygml_HRef_local_id_result;
ecitygml_HRef_local_id_result ecitygml_HRef_local_id(const HRef* self);

bool ecitygml_HRef_is_local(const HRef* self);

void ecitygml_HRef_to_string(const HRef* self, DiplomatWrite* write);

void ecitygml_HRef_destroy(HRef* self);





#endif // HRef_H
