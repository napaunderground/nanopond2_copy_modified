#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include "SFMT.h"

static const uint64_t NUM = 1000000LL;

int 
v1(){
	uint64_t i, cnt=0;
	double x, y, pi;
	const uint64_t seed = 13;
	sfmt_t sfmt;

	cnt = 0;
	sfmt_init_gen_rand(&sfmt, seed);
	for (i = 0; i < NUM; i++) {
		x = sfmt_genrand_res53(&sfmt);
		y = sfmt_genrand_res53(&sfmt);
		if (x * x + y * y < 1.0) {
			cnt++;
		}
	}
	pi = (double)cnt / NUM * 4;
	printf("%lf\n", pi);
	return 0;
}

int v2(){

	uint64_t i=0, j=0, cnt=0;
	const uint64_t seed=13;
	double x, y, pi;
	const uint64_t R_SIZE = 2 * NUM;
	uint64_t size;
	uint64_t *array;
	sfmt_t sfmt;

	size = sfmt_get_min_array_size64(&sfmt);
	if (size < R_SIZE) {
		size = R_SIZE;
	}

	if (posix_memalign((void **)&array, 16, sizeof(double) * size) != 0) {
		printf("%s:%03d  can't allocate memory.\n", __FILE__, __LINE__);
		return 1;
	}

	sfmt_init_gen_rand(&sfmt, seed);
	sfmt_fill_array64(&sfmt, array, size);
	for (i = 0; i < NUM; i++) {
		x = sfmt_to_res53(array[j++]);
		y = sfmt_to_res53(array[j++]);
		if (x * x + y * y < 1.0) {
			cnt++;
		}
	}
	free(array);
	pi = (double)cnt / NUM * 4;
	printf("%lf\n", pi);
	return 0;
}

int main(){
	struct timeval start, end;
	gettimeofday(&start, NULL);
	v1();
	gettimeofday(&end, NULL);
	printf("v1:  %lf\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0);
	gettimeofday(&start, NULL);
	v2();
	gettimeofday(&end, NULL);
	printf("v2:  %lf\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0);

	return 0;
}
