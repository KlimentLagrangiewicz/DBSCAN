#include "help.h"

void fscanfData(const char *fn, double *x, const int n) {
	FILE *fl = fopen(fn, "r");
	if (!fl) {
		printf("Can't open %s file for reading\n", fn);
		exit(1);
	}
	int i = 0;
	while (i < n && !feof(fl)) {
		if (fscanf(fl, "%lf", x + i)) {}
		i++;
	}
	fclose(fl);
}

int getIntWidth(int n) {
	if (n == 0) return 1;
	int res = 0;
	if (n < 0) {
		res = 1;
		n *= -1;
	}
	while (n) {
		res++;
		n /= 10;
	}
	return res;
}

int getMax(const int *y, int n) {
	int max = *(y++);
	while (--n) {
		if (*y > max) max = *y;
		y++;
	}
	return max;
}

void fprintfRes(const char *fn, const int *y, const int n, const int m, const int minPts, const double eps) {
	FILE *fl  = fopen(fn, "a");
	if (!fl) {
		printf("Can't open %s file for writing\n", fn);
		exit(1);
	}
	fprintf(fl, "Result of DBSCAN clustering...\nn = %d, m = %d\nminPts = %d, Eps = %lf\n", n, m, minPts, eps);
	const int width1 = getIntWidth(n), width2 = getIntWidth(getMax(y, n));
	int i;
	for (i = 0; i < n; i++) {
		if (y[i] == -1) fprintf(fl, "Object[%*d] = noise\n", width1, i + 1);
		else fprintf(fl, "Object[%*d] = %*d\n", width1, i + 1, width2, y[i]);
	}
	fputc('\n', fl);
	fclose(fl);
}
