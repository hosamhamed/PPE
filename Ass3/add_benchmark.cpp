//
//  add_benchmark.c
//  Add Microbenchmark Tutorial
//
//  Created by Ricardo Alves on 16/10/14.


#include <stdio.h>
#include <time.h>
#include "gettimeofdayWin.h"
#include <intrin.h>
#include "omp.h"
#include <stdlib.h>
#include <cstdint>
#include <random>

#define NUMBER_OF_RUNS 10
#define TESTS_PER_RUN 1000*1000*1000L
#define ARRAY_SIZE = 128 * 1024 *1024L

struct timeval start_time, end_time;
void add_microbenchmark1(char scale);
void add_microbenchmark2(char scale);
void add_microbenchmark3(char scale);
void add_microbenchmark4(char scale);
void add_microbenchmark5(char scale);
void add_microbenchmark6(char scale);
void add_microbenchmark7(char scale);
void add_microbenchmark8(char scale);
void add_microbenchmark9(char scale);
void add_microbenchmark10(char scale);

void pause(void) {
	printf("press Enter to exit\n");
	getchar();
}


int main(int argc, const char * argv[])
{
	int benchmark = 7;
	printf("Enter benchmark number:");
	scanf("%d", &benchmark);

	switch (benchmark) {
	case 1:
		printf("== Benchmark 1 == Baseline:\n");
		add_microbenchmark1(1);
		break;
	case 2:
		printf("== Benchmark 2 == :\n");
		add_microbenchmark2(1);
		break;
	case 3:
		printf("== Benchmark 3 == :\n");
		add_microbenchmark3(1);
		break;
	case 4:
		printf("== Benchmark 4 == :\n");
		add_microbenchmark4(1);
		break;
	case 5:
		printf("== Benchmark 5 == :\n");
		add_microbenchmark5(10);
		break;
	case 6:
		printf("== Benchmark 6 == :\n");
		add_microbenchmark6(100);
		break;
	case 7:
		printf("== Benchmark 7 == :\n");
		add_microbenchmark7(100);
		break;
	case 8:
		printf("== Benchmark 8 == :\n");
		add_microbenchmark8(100);
		break;
	case 9:
		printf("== Benchmark 9 == :\n");
		add_microbenchmark9(100);
		break;
	case 10:
		printf("== Benchmark 10 == :\n");
		add_microbenchmark10(100);
		break;
	default:
		printf("Invalid benchmark!\n");
	}
	pause();
	return 0;
}



/*
Baseline add benchmark
*/
void add_microbenchmark1(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char * char_data = (char*)malloc(LOCAL_TESTS_PER_RUN * sizeof(char));
	char sum = 1;

	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		for (unsigned long test = 0; test < LOCAL_TESTS_PER_RUN; test += 1) {
			sum += char_data[test];
		}

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		printf("Completed %ld adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}

	free(char_data);
}

/*
add benchmark 2
*/
void add_microbenchmark2(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char * char_data = (char*)malloc(LOCAL_TESTS_PER_RUN * sizeof(char));
	char sum = 1;

	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		for (unsigned long test = 0; test < LOCAL_TESTS_PER_RUN; test += 1) {
			sum += char_data[test];
		}

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		printf("sum: %d  ", sum);
		printf("Completed %ld adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}

	free(char_data);
}



/*
add benchmark 3
*/
void add_microbenchmark3(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	for (unsigned long run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		for (int test = 0; test < LOCAL_TESTS_PER_RUN; test += 1) {
			sum += scale;
		}

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		printf("sum: %d  ", sum);
		printf("Completed %ld adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
}

/*
add benchmark 4
*/
void add_microbenchmark4(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	for (unsigned long run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		__asm mov al, sum; //move sum to the lower significant 8 bits of the 16 bits wide %ax register
		for (int test = 0; test < LOCAL_TESTS_PER_RUN; test += 1) {
			__asm add al, scale; //add resgister %al content with scale variable and storing the result in %al
								 /*
								 See http://locklessinc.com/articles/gcc_asm/
								 Format: Instruction : constraint for %0 (variable) : constraint for %1 (variable)
								 Constraints: +r input, r register
								 */
		}
		__asm mov al, sum; //moving the result from %al back to the variable sum

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		printf("sum: %d  ", sum);
		printf("Completed %ld adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
}

/*
add benchmark 5
*/
void add_microbenchmark5(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	__m128i sum_v0 = _mm_set1_epi8(0);
	__m128i addthis_v = _mm_set1_epi8(scale);

	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		for (long test = 0; test < LOCAL_TESTS_PER_RUN; test += 16) {
			sum_v0 = _mm_add_epi8(addthis_v, sum_v0);
		}

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		for (int i = 0; i < 16; i++)
			sum += ((char*)(&sum_v0))[i];
		printf("sum: %d  ", sum);
		printf("Completed %lu adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
}


/*
add benchmark 6
*/
void add_microbenchmark6(char scale) {

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	__m128i sum_v0 = _mm_set1_epi8(0);
	__m128i sum_v1 = _mm_set1_epi8(0);
	__m128i sum_v2 = _mm_set1_epi8(0);
	__m128i sum_v3 = _mm_set1_epi8(0);
	__m128i addthis_v = _mm_set1_epi8(scale);

	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

		gettimeofday(&start_time, NULL);

		for (long test = 0; test < LOCAL_TESTS_PER_RUN; test += 16 * 4) {
			sum_v0 = _mm_add_epi8(addthis_v, sum_v0);
			sum_v1 = _mm_add_epi8(addthis_v, sum_v1);
			sum_v2 = _mm_add_epi8(addthis_v, sum_v2);
			sum_v3 = _mm_add_epi8(addthis_v, sum_v3);
		}

		gettimeofday(&end_time, NULL);

		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		for (int i = 0; i < 16; i++)
			sum += ((char*)(&sum_v0))[i] + ((char*)(&sum_v1))[i] + ((char*)(&sum_v2))[i] + ((char*)(&sum_v3))[i];
		printf("sum: %d\n", sum);
		printf("Completed %lu adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
}


/*
add benchmark 7
*/
DECLSPEC_NOINLINE void add_microbenchmark7(char scale) {
	//TODO :)

	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	omp_set_num_threads(4);
	for (int run = 0; run < NUMBER_OF_RUNS; run++) {


#pragma omp parallel 
		{
			__m256i sum_v0 = _mm256_set1_epi8(0);
			__m256i sum_v1 = _mm256_set1_epi8(0);
			__m256i sum_v2 = _mm256_set1_epi8(0);
			__m256i sum_v3 = _mm256_set1_epi8(0);
			__m256i addthis_v = _mm256_set1_epi8(scale);

			struct timeval start_time0, end_time0;
			gettimeofday(&start_time0, NULL);
			for (long test = 0; test < LOCAL_TESTS_PER_RUN / 4; test += 32 * 4) {
				sum_v0 = _mm256_add_epi8(addthis_v, sum_v0);
				sum_v1 = _mm256_add_epi8(addthis_v, sum_v1);
				sum_v2 = _mm256_add_epi8(addthis_v, sum_v2);
				sum_v3 = _mm256_add_epi8(addthis_v, sum_v3);
			}
#pragma omp barrier
			gettimeofday(&end_time0, NULL);
			if (omp_get_thread_num() == 0) {
				start_time = start_time0;
				end_time = end_time0;
			}
#pragma omp critical
			for (int i = 0; i < 16; i++)
				sum += ((char*)(&sum_v0))[i] + ((char*)(&sum_v1))[i] + ((char*)(&sum_v2))[i] + ((char*)(&sum_v3))[i];
		}
		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		//for (int i = 0; i<16; i++)
		//	sum += ((char*)(&sum_v0))[i] + ((char*)(&sum_v1))[i] + ((char*)(&sum_v2))[i] + ((char*)(&sum_v3))[i];
		printf("sum: %d\n", sum);
		printf("Completed %lu adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}



}
/*
add benchmark 8
*/
DECLSPEC_NOINLINE void add_microbenchmark8(char scale) {
	//TODO :)
	float scale_float = (float)scale;
	unsigned long LOCAL_TESTS_PER_RUN = TESTS_PER_RUN * scale;

	char sum = 1;

	omp_set_num_threads(4);
	for (int run = 0; run < NUMBER_OF_RUNS; run++) {


#pragma omp parallel 
		{
			__m256 sum_v0 = _mm256_set1_ps(0.0);
			__m256 sum_v1 = _mm256_set1_ps(0.0);
			__m256 sum_v2 = _mm256_set1_ps(0.0);
			__m256 sum_v3 = _mm256_set1_ps(0.0);
			__m256 addthis_v = _mm256_set1_ps(scale_float);

			struct timeval start_time0, end_time0;
			gettimeofday(&start_time0, NULL);
			for (long test = 0; test < LOCAL_TESTS_PER_RUN / 4; test += 8 * 4) {
				sum_v0 = _mm256_add_ps(addthis_v, sum_v0);
				sum_v1 = _mm256_add_ps(addthis_v, sum_v1);
				sum_v2 = _mm256_add_ps(addthis_v, sum_v2);
				sum_v3 = _mm256_add_ps(addthis_v, sum_v3);
			}
#pragma omp barrier
			gettimeofday(&end_time0, NULL);
			if (omp_get_thread_num() == 0) {
				start_time = start_time0;
				end_time = end_time0;
			}
#pragma omp critical
			for (int i = 0; i < 16; i++)
				sum += ((char*)(&sum_v0))[i] + ((char*)(&sum_v1))[i] + ((char*)(&sum_v2))[i] + ((char*)(&sum_v3))[i];
		}
		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		//for (int i = 0; i<16; i++)
		//	sum += ((char*)(&sum_v0))[i] + ((char*)(&sum_v1))[i] + ((char*)(&sum_v2))[i] + ((char*)(&sum_v3))[i];
		printf("sum: %d ", sum);
		printf("Completed %lu adds in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
}


/*
add benchmark 9 loading sequential
*/
DECLSPEC_NOINLINE void add_microbenchmark9(char scale) {
	//TODO :)
	float scale_float = (float)scale;
	unsigned long LOCAL_TESTS_PER_RUN = 1024 * 1024 * scale;
	long* data = (long*)malloc(LOCAL_TESTS_PER_RUN * sizeof(long));
	long X = 0;

	int nth, nthread;
	printf("Number of Threads: ");
	scanf("%d", &nth);
	printf("\nlong %d\n", sizeof(long));
	omp_set_num_threads(nth);
	double sum_GOPS = 0, avg_GOPS;
	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

#pragma omp parallel 
		{
			struct timeval start_time0, end_time0;
			gettimeofday(&start_time0, NULL);
			//int id = omp_get_thread_num();
			//if (id == 0)
			//printf("Number of Threads= %d\n", omp_get_num_threads());

			for (unsigned long test = 0; test < LOCAL_TESTS_PER_RUN / nth; test += nth) {
				X = data[test];
				//__asm mov var1, sum;
			}
#pragma omp barrier
			gettimeofday(&end_time0, NULL);
			if (omp_get_thread_num() == 0) {
				start_time = start_time0;
				end_time = end_time0;
			}
		}
		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		sum_GOPS += GOPS;
		printf("X: %d ", X);
		printf("Completed %lu loads in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
	avg_GOPS = sum_GOPS / NUMBER_OF_RUNS * 4;
	printf("\nAverage GiB/s = %g\n", avg_GOPS);
	//	printf("Number of Threads= %d\n", nthread);
	//	printf("Number of Threads= %d\n", nthread);
	getchar();
}


/*
add benchmark 10 loading random
*/
DECLSPEC_NOINLINE void add_microbenchmark10(char scale) {
	//TODO :)
	float scale_float = (float)scale;
	int CACHE_LINE = 1;
	unsigned long LOCAL_TESTS_PER_RUN = 1024 * 1024 * scale;
	long* data = (long*)malloc(LOCAL_TESTS_PER_RUN * sizeof(long));
	long* index = (long*)malloc(LOCAL_TESTS_PER_RUN * sizeof(long));
	long X = 0;

	int nth;
	printf("Number of Threads: ");
	scanf("%d", &nth);

	omp_set_num_threads(nth);
	double sum_GOPS = 0, avg_GOPS;

	/* Seed */
	std::random_device rd;

	/* Random number generator */
	std::default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	std::uniform_int_distribution<long unsigned> distribution(0, 0xFFFFFFFF);

	for (unsigned long i = 0; i < LOCAL_TESTS_PER_RUN; i++)
	{
		index[i] = distribution(generator) % LOCAL_TESTS_PER_RUN;
	}

	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

#pragma omp parallel
		{
			struct timeval start_time0, end_time0;
			gettimeofday(&start_time0, NULL);
			for (unsigned long test = 0; test < LOCAL_TESTS_PER_RUN / nth; test += nth) {
				X = data[index[test]];
				/*printf("r = %lu\n", index[test]);
				getchar();*/
				//__asm mov var1, sum;
			}
#pragma omp barrier
			gettimeofday(&end_time0, NULL);
			if (omp_get_thread_num() == 0) {
				start_time = start_time0;
				end_time = end_time0;
			}
		}
		double time_in_sec = (end_time.tv_sec + end_time.tv_usec / 1000000.0) - (start_time.tv_sec + start_time.tv_usec / 1000000.0);
		double GOPS = (LOCAL_TESTS_PER_RUN / time_in_sec) / 1000000000;
		sum_GOPS += GOPS;
		printf("X: %d ", X);
		printf("Completed %lu loads in %g seconds for %g GOPS.\n", LOCAL_TESTS_PER_RUN, time_in_sec, GOPS);
	}
	avg_GOPS = sum_GOPS / NUMBER_OF_RUNS * 4;
	printf("\nAverage GiB/s = %g\n", avg_GOPS);
	getchar();
}
