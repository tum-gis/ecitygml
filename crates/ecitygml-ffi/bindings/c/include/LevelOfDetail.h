#ifndef LevelOfDetail_H
#define LevelOfDetail_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Error.d.h"

#include "LevelOfDetail.d.h"






size_t ecitygml_LevelOfDetail_as_index(LevelOfDetail self);

typedef struct ecitygml_LevelOfDetail_try_from_result {union {LevelOfDetail ok; Error* err;}; bool is_ok;} ecitygml_LevelOfDetail_try_from_result;
ecitygml_LevelOfDetail_try_from_result ecitygml_LevelOfDetail_try_from(uint8_t value);





#endif // LevelOfDetail_H
