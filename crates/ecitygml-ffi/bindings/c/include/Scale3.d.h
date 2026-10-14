#ifndef Scale3_D_H
#define Scale3_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef struct Scale3 {
  double x;
  double y;
  double z;
} Scale3;

typedef struct Scale3_option {union { Scale3 ok; }; bool is_ok; } Scale3_option;



#endif // Scale3_D_H
