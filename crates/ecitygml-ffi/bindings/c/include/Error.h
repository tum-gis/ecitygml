#ifndef Error_H
#define Error_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "ErrorKind.d.h"

#include "Error.d.h"






ErrorKind ecitygml_Error_kind(const Error* self);

void ecitygml_Error_message(const Error* self, DiplomatWrite* write);

void ecitygml_Error_destroy(Error* self);





#endif // Error_H
