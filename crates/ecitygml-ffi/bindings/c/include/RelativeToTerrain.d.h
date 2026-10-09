#ifndef RelativeToTerrain_D_H
#define RelativeToTerrain_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum RelativeToTerrain {
  RelativeToTerrain_EntirelyAboveTerrain = 0,
  RelativeToTerrain_SubstantiallyAboveTerrain = 1,
  RelativeToTerrain_SubstantiallyAboveAndBelowTerrain = 2,
  RelativeToTerrain_SubstantiallyBelowTerrain = 3,
  RelativeToTerrain_EntirelyBelowTerrain = 4,
} RelativeToTerrain;

typedef struct RelativeToTerrain_option {union { RelativeToTerrain ok; }; bool is_ok; } RelativeToTerrain_option;



#endif // RelativeToTerrain_D_H
