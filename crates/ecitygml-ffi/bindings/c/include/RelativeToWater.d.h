#ifndef RelativeToWater_D_H
#define RelativeToWater_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum RelativeToWater {
  RelativeToWater_EntirelyAboveWaterSurface = 0,
  RelativeToWater_SubstantiallyAboveWaterSurface = 1,
  RelativeToWater_SubstantiallyAboveAndBelowWaterSurface = 2,
  RelativeToWater_SubstantiallyBelowWaterSurface = 3,
  RelativeToWater_EntirelyBelowWaterSurface = 4,
  RelativeToWater_TemporarilyAboveAndBelowWaterSurface = 5,
} RelativeToWater;

typedef struct RelativeToWater_option {union { RelativeToWater ok; }; bool is_ok; } RelativeToWater_option;



#endif // RelativeToWater_D_H
