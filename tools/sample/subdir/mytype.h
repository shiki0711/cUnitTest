#ifndef INCLUDE_MYTYPE_H_
#define INCLUDE_MYTYPE_H_

typedef signed int INT;
typedef unsigned int UINT;

typedef struct {
  int a;
  float b;
  char c[10];
} T_MY_STRUCT;

#define MY_DEFINATION (1)

typedef int (*my_function)(const char* a, int b, float c);

#endif
