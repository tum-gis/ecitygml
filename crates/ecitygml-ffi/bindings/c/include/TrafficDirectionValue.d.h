#ifndef TrafficDirectionValue_D_H
#define TrafficDirectionValue_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum TrafficDirectionValue {
  TrafficDirectionValue_Forwards = 0,
  TrafficDirectionValue_Backwards = 1,
  TrafficDirectionValue_Both = 2,
} TrafficDirectionValue;

typedef struct TrafficDirectionValue_option {union { TrafficDirectionValue ok; }; bool is_ok; } TrafficDirectionValue_option;



#endif // TrafficDirectionValue_D_H
