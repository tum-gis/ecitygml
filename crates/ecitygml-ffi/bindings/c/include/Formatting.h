#ifndef Formatting_H
#define Formatting_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "Formatting.d.h"






Formatting* ecitygml_Formatting_compact(void);

Formatting* ecitygml_Formatting_new_line(void);

Formatting* ecitygml_Formatting_indent(uint8_t char_, size_t size);

void ecitygml_Formatting_destroy(Formatting* self);





#endif // Formatting_H
