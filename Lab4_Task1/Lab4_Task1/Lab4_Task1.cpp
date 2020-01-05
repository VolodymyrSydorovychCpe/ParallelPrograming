#include <iostream>
#include <omp.h>

int main() {
#ifdef _OPENMP
	printf("_OPENMP Defined\n");
#else
	printf("_OPENMP UnDefined\n");
#endif
	return 0;
}
