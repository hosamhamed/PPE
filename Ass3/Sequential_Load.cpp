
/*
add benchmark 9 loading sequential
*/
DECLSPEC_NOINLINE void add_microbenchmark9(char scale) {
	//TODO :)
	float scale_float = (float)scale;
	unsigned long LOCAL_TESTS_PER_RUN = 1024*1024 * scale;
	long* data = (long*)malloc(LOCAL_TESTS_PER_RUN * sizeof(long));
	int32_t X = 0;

	int nth;
	printf("Number of Threads: ");
	scanf("%d", &nth);

	omp_set_num_threads(nth);
	double sum_GOPS = 0, avg_GOPS;
	for (int run = 0; run < NUMBER_OF_RUNS; run++) {

#pragma omp parallel
		{

			struct timeval start_time0, end_time0;
			gettimeofday(&start_time0, NULL);
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
	avg_GOPS = sum_GOPS / NUMBER_OF_RUNS;
	printf("\nAverage GOPS = %g\n", avg_GOPS);
}
