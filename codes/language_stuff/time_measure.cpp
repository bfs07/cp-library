clock_t start = clock();

/* Execute the program */

clock_t end = clock();

double time_taken = double(end - start) / double(CLOCKS_PER_SEC);