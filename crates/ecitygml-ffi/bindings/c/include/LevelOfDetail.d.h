#ifndef LevelOfDetail_D_H
#define LevelOfDetail_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum LevelOfDetail {
  LevelOfDetail_Zero = 0,
  LevelOfDetail_One = 1,
  LevelOfDetail_Two = 2,
  LevelOfDetail_Three = 3,
} LevelOfDetail;

typedef struct LevelOfDetail_option {union { LevelOfDetail ok; }; bool is_ok; } LevelOfDetail_option;



#endif // LevelOfDetail_D_H
