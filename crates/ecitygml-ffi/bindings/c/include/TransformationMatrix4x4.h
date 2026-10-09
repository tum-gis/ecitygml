#ifndef TransformationMatrix4x4_H
#define TransformationMatrix4x4_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Error.d.h"

#include "TransformationMatrix4x4.d.h"






typedef struct ecitygml_TransformationMatrix4x4_get_result {union {double ok; Error* err;}; bool is_ok;} ecitygml_TransformationMatrix4x4_get_result;
ecitygml_TransformationMatrix4x4_get_result ecitygml_TransformationMatrix4x4_get(const TransformationMatrix4x4* self, size_t row, size_t column);

void ecitygml_TransformationMatrix4x4_destroy(TransformationMatrix4x4* self);





#endif // TransformationMatrix4x4_H
