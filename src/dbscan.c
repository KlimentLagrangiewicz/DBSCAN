#include "dbscan.h"

static double distEv(const double *x, const double *c, const int m) {
	double d, r = 0;
	int i = 0;
	while (i++ < m) {
		d = *(x++) - *(c++);
		r += d * d;
	}
	return sqrt(r);
}

static void neighbors_matr(const double *x, unsigned char *nei, const int n, const int m, const double eps) {
	int i, j;
	i = 0;
	while (i < n) {
		j = 0;
		while (j < n) {
			*(nei++) = ((i != j) && (distEv(&x[i], &x[j], m) <= eps)) ? 1 : 0;
			j += m;
		}
		i += m;
	}
}

static int n_nums(const unsigned char *nei, const int n) {
	int i, r;
	i = r = 0;
	while (i++ < n) {
		if (*(nei++)) r++;
	}
	return r;
}

static void marker(const unsigned char *neighbors, int *status, const int n, const int k, const int mark) {
	const int buf = k * n;
	int i = 0;
	while (i < n) {
		if ((status[i] == -1) && (neighbors[buf + i])) {
			status[i] = mark;
			marker(neighbors, status, n, i, mark);
		}
		i++;
	}
}

void dbscan(const double *x, int *res, const int n, const int m, const int minPts, const double eps) {
	memset(res, -1, n * sizeof(int));
	unsigned char *neighbors = (unsigned char*)malloc(n * n * sizeof(unsigned char));
	neighbors_matr(x, &neighbors[0], n * m, m, eps);
	int i, count;
	i = count = 0;
	while (i < n) {
		if ((res[i] == -1) && (n_nums(&neighbors[i * n], n) >= minPts)) {
			res[i] = count;
			marker(neighbors, res, n, i, count);
			count++;
		}
		i++;
	}
	free(neighbors);
}
