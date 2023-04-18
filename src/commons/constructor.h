#ifndef CONSTRUCTOR_H_
#define CONSTRUCTOR_H_

#include <stdlib.h>
#define NEW(var, type)  type *var = malloc( sizeof(type) );
#define FREE(var)  free(var);

#endif