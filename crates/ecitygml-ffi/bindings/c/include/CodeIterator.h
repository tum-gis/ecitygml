#ifndef CodeIterator_H
#define CodeIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "CodeIterator.d.h"






const Code* ecitygml_CodeIterator_next(CodeIterator* self);

void ecitygml_CodeIterator_destroy(CodeIterator* self);





#endif // CodeIterator_H
