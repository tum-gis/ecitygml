#ifndef ExternalReference_H
#define ExternalReference_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "ExternalReference.d.h"






DiplomatStringView ecitygml_ExternalReference_target_resource(const ExternalReference* self);

typedef struct ecitygml_ExternalReference_information_system_result {union {DiplomatStringView ok; }; bool is_ok;} ecitygml_ExternalReference_information_system_result;
ecitygml_ExternalReference_information_system_result ecitygml_ExternalReference_information_system(const ExternalReference* self);

typedef struct ecitygml_ExternalReference_relation_type_result {union {DiplomatStringView ok; }; bool is_ok;} ecitygml_ExternalReference_relation_type_result;
ecitygml_ExternalReference_relation_type_result ecitygml_ExternalReference_relation_type(const ExternalReference* self);

void ecitygml_ExternalReference_destroy(ExternalReference* self);





#endif // ExternalReference_H
