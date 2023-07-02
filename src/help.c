#include "help.h"

void fscanfData(const char *fn, double *x, const int n) {
	FILE *fl = fopen(fn, "r");
	if (fl == NULL) {
		printf("Can't open %s file for reading...\n", fn);
		exit(1);
	}
	int i = 0;
	while ((i < n) && !feof(fl)) {
		if (fscanf(fl, "%lf", &x[i])) {}
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
			fprintf(fl, "Object[ %d ] = %d;\n", i, y[i]);
		}
		i++;
	}
	fprintf(fl, "\n");
	fclose(fl);
}
