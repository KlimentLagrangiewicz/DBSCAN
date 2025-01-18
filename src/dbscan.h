#ifndef DBSCAN_H_
#define DBSCAN_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>

double getDistance(const double *x1, const double *x2, int m);
double getAvDist(const double *x, const int n, const int m);
void autoscaling(double* const x, const int n, const int m, double *eps);
void setNeighborsRow(unsigned char *ptrRow, const double *const x, const double* X, int n, const int m, const double eps);
unsigned char* getNeighborsMatr(const double *x, const int n, const int m, const double eps);
int neighborsNum(const unsigned char *nei, int n);
void marking(const unsigned char* const neighbors, int* const status, const int n, const int k, const int mark);
void dbscan(const double* const X, int* const y, const int n, const int m, const int minPts, double eps);

#endif
