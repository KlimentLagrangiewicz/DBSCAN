#include "dbscan.h"

double getDistance(const double *x1, const double *x2, int m) {
	double d, r = 0.0;
	while (m--) {
		d = *(x1++) - *(x2++);
		r += d * d;
	}
	return sqrt(r);
}

double getAvDist(const double *x, const int n, const int m) {
	double res = 0.0;
	int i, j;
	for (i = 0; i < n * m; i += m) {
		for (j = i + m; j < n * m; j += m) {
			res += getDistance(x + i, x + j, m);
		}
	}
	return 2.0 * res / (n * n + n);
}

void autoscaling(double* const x, const int n, const int m, double *eps) {
	const double beforeAvDist = getAvDist(x, n, m);
	const int s = n * m;
	int j;
	for (j = 0; j < m; j++) {
		double sd, Ex = 0.0, Exx = 0.0, *ptr;
		for (ptr = x + j; ptr < x + s; ptr += m) {
			sd = *ptr;
			Ex += sd;
			Exx += sd * sd;
		}
		Exx /= n;
		Ex /= n;
		sd = sqrt(Exx - Ex * Ex);
		for (ptr = x + j; ptr < x + s; ptr += m) {
			*ptr = (*ptr - Ex) / sd;
		}
	}
	const double afterAvDist = getAvDist(x, n, m);
	*eps /= beforeAvDist / afterAvDist;
}

void setNeighborsRow(unsigned char *ptrRow, const double *const x, const double* X, int n, const int m, const double eps) {
	while (n--) {
		*(ptrRow++) = (x != X && getDistance(x, X, m) <= eps) ? 1 : 0;
		X += m;
	}
}

unsigned char* getNeighborsMatr(const double *x, const int n, const int m, const double eps) {
	unsigned char* nMatr = (unsigned char*)malloc(n * n * sizeof(unsigned char));
	int i;
	for (i = 0; i < n; i++) {
		setNeighborsRow(nMatr + i * n, x + i * m, x, n, m, eps);
	}
	return nMatr;
}

int neighborsNum(const unsigned char *nei, int n) {
	int r = 1;
	while (n--) if (*(nei++)) r++;
	return r;
}

void marking(const unsigned char* const neighbors, int* const status, const int n, const int k, const int mark) {
	int i;
	for (i = 0; i < n; i++) {
		if (status[i] == -1 && neighbors[k + i]) {
			status[i] = mark;
			marking(neighbors, status, n, i * n, mark);
		}
	}
}

void dbscan(const double* const X, int* const y, const int n, const int m, const int minPts, double eps) {
	double *x = (double*)malloc(n * m * sizeof(double));
	memcpy(x, X, n * m * sizeof(double));
	autoscaling(x, n, m, &eps);
	memset(y, -1, n * sizeof(int));
	unsigned char *neighbors = getNeighborsMatr(x, n, m, eps);
	int i, count = 0;
	for (i = 0; i < n; i++) {
		if (y[i] == -1 && neighborsNum(neighbors + i * n, n) >= minPts) {
			y[i] = count;
			marking(neighbors, y, n, i * n, count);
			count++;
		}
	}
	free(x);
	free(neighbors);
}
