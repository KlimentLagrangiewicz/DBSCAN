#include "dbscan.h"

double distEv(const double *x, const double *c, const int m) {
	double d, r = 0;
	int i = 0;
	while (i++ < m) {
		d = *(x++) - *(c++);
		r += d * d;
	}
	return sqrt(r);
}

double getAvDist(const double *x, const int n, const int m) {
	double res = 0;
	int i, j;
	for (i = 0; i < n * m; i += m) {
		for (j = i + m; j < n * m; j += m) {
			res += distEv(&x[i], &x[j], m);
		}
	}
	return 2 * res / (n * n + n);
}

void autoscaling(double *x, const int n, const int m, double *eps) {
	double beforeAvDist = getAvDist(x, n, m), afterAvDist, sd, Ex, Exx;
	const int s = n * m;
	int i, j = 0;
	while (j < m) {
		i = j;
		Ex = Exx = 0;
		while (i < s) {
			sd = x[i];
			Ex += sd;
			Exx += sd * sd;
			i += m;
		}
		Exx /= n;
		Ex /= n;
		sd = sqrt(Exx - Ex * Ex);
		i = j;
		while (i < s) {
			x[i] = (x[i] - Ex) / sd;
			i += m;
		}
		j++;
	}
	afterAvDist = getAvDist(x, n, m);
	*eps /= (beforeAvDist / afterAvDist);
}


void neighbors_matr(const double *x, unsigned char *nei, const int n, const int m, const double eps) {
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

int n_nums(const unsigned char *nei, const int n) {
	int i, r;
	i = r = 0;
	while (i++ < n) {
		if (*(nei++)) r++;
	}
	return r;
}

void marker(const unsigned char* const neighbors, int* const status, const int n, const int k, const int mark) {
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

void dbscan(const double* const X, int* const res, const int n, const int m, const int minPts, const double epsIn) {
	double *x = (double*)malloc(n * m * sizeof(double));
	memcpy(&x[0], &X[0], n * m * sizeof(double));
	double eps = epsIn;
	autoscaling(x, n, m, &eps);
	memset(&res[0], -1, n * sizeof(int));
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
	free(x);
	free(neighbors);
}
