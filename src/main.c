#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "help.h"
#include "dbscan.h"

long long timeValue = 0;

unsigned long long time_RDTSC() {
	union ticks {
		unsigned long long tx;
		struct dblword {
			long tl, th;
		} dw;
	} t;
	__asm__ ("rdtsc\n"
	  : "=a" (t.dw.tl), "=d"(t.dw.th)
	  );
	return t.tx;
}

void time_start() { timeValue = time_RDTSC(); }

long long time_stop() { return time_RDTSC() - timeValue; }

int main(int argc, char **argv) {
	if (argc < 7) {
		puts("Not enough parameters!");
		exit(1);
	}
	const int n = atoi(argv[1]), m = atoi(argv[2]), minPts = atoi(argv[3]);
	double eps = strtod(argv[4], NULL), eps2 = eps;
	if ((n < 0) || (m < 0) || (minPts < 0) || (eps < 0)) {
		puts("Value of parameters is incorrect...");
		exit(1);
	}
	double *x =(double*)malloc(n * m * sizeof(double));
	int *y = (int*)malloc(n * sizeof(int));
	fscanfData(argv[5], x, n * m);
	autoscaling(x, n, m, &eps);
	long long t;
	clock_t cl = clock();
	time_start();
	dbscan(x, y, n, m, minPts, eps);
	t = time_stop();
	cl = clock() - cl;
	fprintfRes(argv[6], y, n, minPts, eps2);
	if (t < 0) {
		printf("Time for DBSCAN clustering = %lf s.\n", (double)cl);
	} else {
		printf("Time for DBSCAN clustering = %lld CPU clocks;\n", t);
	}
	free(x);
	free(y);
	return 0;
}
