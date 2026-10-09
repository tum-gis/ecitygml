#ifndef Code_H
#define Code_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "Code.d.h"






DiplomatStringView ecitygml_Code_value(const Code* self);

typedef struct ecitygml_Code_code_space_result {union {DiplomatStringView ok; }; bool is_ok;} ecitygml_Code_code_space_result;
ecitygml_Code_code_space_result ecitygml_Code_code_space(const Code* self);

void ecitygml_Code_destroy(Code* self);





#endif // Code_H
