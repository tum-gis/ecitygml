#ifndef HeightStatusValue_D_H
#define HeightStatusValue_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum HeightStatusValue {
  HeightStatusValue_Estimated = 0,
  HeightStatusValue_Measured = 1,
} HeightStatusValue;

typedef struct HeightStatusValue_option {union { HeightStatusValue ok; }; bool is_ok; } HeightStatusValue_option;



#endif // HeightStatusValue_D_H
