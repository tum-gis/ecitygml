#ifndef CitygmlFormat_D_H
#define CitygmlFormat_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum CitygmlFormat {
  CitygmlFormat_Gml = 0,
  CitygmlFormat_GmlZst = 1,
  CitygmlFormat_GmlGz = 2,
} CitygmlFormat;

typedef struct CitygmlFormat_option {union { CitygmlFormat ok; }; bool is_ok; } CitygmlFormat_option;



#endif // CitygmlFormat_D_H
