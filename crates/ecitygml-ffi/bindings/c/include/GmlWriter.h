#ifndef GmlWriter_H
#define GmlWriter_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityModel.d.h"
#include "CitygmlFormat.d.h"
#include "Error.d.h"
#include "Formatting.d.h"

#include "GmlWriter.d.h"






GmlWriter* ecitygml_GmlWriter_new(CitygmlFormat format);

typedef struct ecitygml_GmlWriter_from_path_result {union {GmlWriter* ok; Error* err;}; bool is_ok;} ecitygml_GmlWriter_from_path_result;
ecitygml_GmlWriter_from_path_result ecitygml_GmlWriter_from_path(DiplomatStringView path);

typedef struct ecitygml_GmlWriter_from_base_path_with_format_result {union {GmlWriter* ok; Error* err;}; bool is_ok;} ecitygml_GmlWriter_from_base_path_with_format_result;
ecitygml_GmlWriter_from_base_path_with_format_result ecitygml_GmlWriter_from_base_path_with_format(DiplomatStringView base_path, CitygmlFormat format);

void ecitygml_GmlWriter_with_formatting(GmlWriter* self, const Formatting* formatting);

typedef struct ecitygml_GmlWriter_finish_result {union { Error* err;}; bool is_ok;} ecitygml_GmlWriter_finish_result;
ecitygml_GmlWriter_finish_result ecitygml_GmlWriter_finish(GmlWriter* self, const CityModel* city_model);

DiplomatU8View ecitygml_GmlWriter_data(const GmlWriter* self);

void ecitygml_GmlWriter_destroy(GmlWriter* self);





#endif // GmlWriter_H
