#ifndef CONSTRUCTOR_H_
#define CONSTRUCTOR_H_

#define NEW(var, type)  type *var = malloc( sizeof(type) );
#define FREE(var)  free(var);

#endif
