#include "help.h"

void fscanfData(const char *fn, double *x, const int n) {
	FILE *fl = fopen(fn, "r");
	if (fl == NULL) {
		printf("Can't open %s file for reading...\n", fn);
		exit(1);
	}
	int i = 0;
	while ((i < n) && !feof(fl)) {
		fscanf(fl, "%lf", &x[i]);
		i++;
	}
	fclose(fl);
}

void fprintfRes(const char *fn, const int *y, const int n, const int minPts, const double eps) {
	FILE *fl  = fopen(fn, "a");
	if (fl == NULL) {
		printf("Can't open %s file for writing...\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of DBSCAN clustering...\nminPts = %d;\nEps = %lf;\n", minPts, eps);
	int i = 0;
	while (i < n) {
		if (y[i] == -1) {
			fprintf(fl, "Object[ %d ] = Noise;\n", i);
		} else {
			fprintf(fl, "Object[ %d ] = %d cluster;\n", i, y[i]);
		}
		i++;
	}
	fprintf(fl, "\n");
	fclose(fl);
}

static double getDist(const double *x1, const double *x2, const int m) {
	double d, r = 0;
	int i = 0;
	while (i++ < m) {
		d = *(x1++) - *(x2++);
		r += d * d;
	}
	return sqrt(r);
}

static double getAvDist(const double *x, const int n, const int m) {
	double res = 0;
	int i, j;
	for (i = 0; i < n * m; i += m) {
		for (j = i + m; j < n * m; j += m) {
			res += getDist(&x[i], &x[j], m);
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
