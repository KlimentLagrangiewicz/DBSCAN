#ifndef DBSCAN_H_
#define DBSCAN_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>

void dbscan(const double *x, int *res, const int n, const int m, const int minPts, const double eps);

#endif
