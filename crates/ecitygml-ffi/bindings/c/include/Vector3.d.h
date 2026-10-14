#ifndef Vector3_D_H
#define Vector3_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef struct Vector3 {
  double x;
  double y;
  double z;
} Vector3;

typedef struct Vector3_option {union { Vector3 ok; }; bool is_ok; } Vector3_option;



#endif // Vector3_D_H
