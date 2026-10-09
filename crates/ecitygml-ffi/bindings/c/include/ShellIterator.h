#ifndef ShellIterator_H
#define ShellIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Shell.d.h"

#include "ShellIterator.d.h"






const Shell* ecitygml_ShellIterator_next(ShellIterator* self);

void ecitygml_ShellIterator_destroy(ShellIterator* self);





#endif // ShellIterator_H
