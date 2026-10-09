#ifndef GmlReader_H
#define GmlReader_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "CityModel.d.h"
#include "CitygmlFormat.d.h"
#include "Error.d.h"

#include "GmlReader.d.h"






GmlReader* ecitygml_GmlReader_new(DiplomatU8View data, CitygmlFormat format);

typedef struct ecitygml_GmlReader_from_path_result {union {GmlReader* ok; Error* err;}; bool is_ok;} ecitygml_GmlReader_from_path_result;
ecitygml_GmlReader_from_path_result ecitygml_GmlReader_from_path(DiplomatStringView path);

void ecitygml_GmlReader_with_rebuild_object_bounds(GmlReader* self, bool rebuild_object_bounds);

typedef struct ecitygml_GmlReader_finish_result {union {CityModel* ok; Error* err;}; bool is_ok;} ecitygml_GmlReader_finish_result;
ecitygml_GmlReader_finish_result ecitygml_GmlReader_finish(GmlReader* self);

void ecitygml_GmlReader_destroy(GmlReader* self);





#endif // GmlReader_H
