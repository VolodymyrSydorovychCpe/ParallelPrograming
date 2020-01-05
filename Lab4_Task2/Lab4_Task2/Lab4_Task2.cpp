#include <iostream>
#include <omp.h>
#include <Windows.h>


int main()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	std::cout << "Windows threads: " << si.dwNumberOfProcessors;

	int cores = omp_get_max_threads();
	std::cout << "Omp threads: " << cores;

	return 0;
}
