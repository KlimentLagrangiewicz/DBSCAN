#ifndef DBSCAN_H_
#define DBSCAN_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>

double distEv(const double *x, const double *c, const int m);
double getAvDist(const double *x, const int n, const int m);
void autoscaling(double *x, const int n, const int m, double *eps);
void neighbors_matr(const double *x, unsigned char *nei, const int n, const int m, const double eps);
int n_nums(const unsigned char *nei, const int n);
void marker(const unsigned char* const neighbors, int* const status, const int n, const int k, const int mark);
void dbscan(const double* const X, int* const res, const int n, const int m, const int minPts, const double epsIn);

#endif
