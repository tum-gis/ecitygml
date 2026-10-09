#ifndef MimeTypeValue_H
#define MimeTypeValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "MimeTypeValue.d.h"






const Code* ecitygml_MimeTypeValue_code(const MimeTypeValue* self);

DiplomatStringView ecitygml_MimeTypeValue_value(const MimeTypeValue* self);

void ecitygml_MimeTypeValue_destroy(MimeTypeValue* self);





#endif // MimeTypeValue_H
