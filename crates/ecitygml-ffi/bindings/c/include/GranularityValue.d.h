#ifndef GranularityValue_D_H
#define GranularityValue_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum GranularityValue {
  GranularityValue_Lane = 0,
  GranularityValue_Way = 1,
} GranularityValue;

typedef struct GranularityValue_option {union { GranularityValue ok; }; bool is_ok; } GranularityValue_option;



#endif // GranularityValue_D_H
