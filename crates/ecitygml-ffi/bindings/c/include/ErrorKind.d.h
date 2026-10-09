#ifndef ErrorKind_D_H
#define ErrorKind_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum ErrorKind {
  ErrorKind_InvalidArgument = 0,
  ErrorKind_Io = 1,
  ErrorKind_Parse = 2,
  ErrorKind_UnresolvedReference = 3,
} ErrorKind;

typedef struct ErrorKind_option {union { ErrorKind ok; }; bool is_ok; } ErrorKind_option;



#endif // ErrorKind_D_H
