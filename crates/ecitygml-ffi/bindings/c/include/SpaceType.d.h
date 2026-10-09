#ifndef SpaceType_D_H
#define SpaceType_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum SpaceType {
  SpaceType_Closed = 0,
  SpaceType_Open = 1,
  SpaceType_SemiOpen = 2,
} SpaceType;

typedef struct SpaceType_option {union { SpaceType ok; }; bool is_ok; } SpaceType_option;



#endif // SpaceType_D_H
