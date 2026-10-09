#ifndef DirectPosition_H
#define DirectPosition_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Error.d.h"

#include "DirectPosition.d.h"






typedef struct ecitygml_DirectPosition_new_result {union {DirectPosition* ok; Error* err;}; bool is_ok;} ecitygml_DirectPosition_new_result;
ecitygml_DirectPosition_new_result ecitygml_DirectPosition_new(double x, double y, double z);

double ecitygml_DirectPosition_x(const DirectPosition* self);

double ecitygml_DirectPosition_y(const DirectPosition* self);

double ecitygml_DirectPosition_z(const DirectPosition* self);

void ecitygml_DirectPosition_destroy(DirectPosition* self);





#endif // DirectPosition_H
