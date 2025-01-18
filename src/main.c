#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "dbscan.h"


int main(int argc, char **argv) {
	if (argc < 7) {
		puts("Not enough parameters");
		exit(1);
	}
	const int n = atoi(argv[2]), m = atoi(argv[3]), minPts = atoi(argv[4]);
	const double eps = strtod(argv[5], NULL);
	if (n < 1 || m < 1 || minPts < 1 || eps <= 0 || minPts >= n) {
		puts("Values of parameters are incorrect...");
		exit(1);
	}
	double *x =(double*)malloc(n * m * sizeof(double));
	int *y = (int*)malloc(n * sizeof(int));
	fscanfData(argv[1], x, n * m);
	double cl = clock();
	dbscan(x, y, n, m, minPts, eps);
	cl = clock() - cl;
	cl /= CLOCKS_PER_SEC;
	fprintfRes(argv[6], y, n, m, minPts, eps);
	printf("Time for DBSCAN clustering = %lf s.\n", cl);
	free(x);
	free(y);
	return 0;
}
