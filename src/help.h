#ifndef HELP_H_
#define HELP_H_

#include <stdio.h>
#include <stdlib.h>

void fscanfData(const char *fn, double *x, const int n);
void fprintfRes(const char *fn, const int *y, const int n, const int minPts, const double eps);

#endif
