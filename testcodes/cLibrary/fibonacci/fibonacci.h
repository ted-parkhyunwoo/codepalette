#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ULL;
extern ULL* memo;
void initMemo(int n);
ULL getFib(int n);
void freeMemo();

#endif