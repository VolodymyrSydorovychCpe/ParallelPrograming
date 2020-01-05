#include <iostream>
#include <omp.h>
#include <Windows.h>
#include <functional>
#include <string>
#include <map>

std::string const TIME = "time";
std::string const PI = "pi";

std::map<std::string, double> countTime(int n, std::function<double(int n)> function) {
	std::map<std::string, double> result;

	double start = omp_get_wtime();
	result[PI] = function(n);
	result[TIME] = omp_get_wtime() - start;
	return result;
}

double formula_Bailey_Borwein_Plouffe(int N)
{
	double pi = 0;
	for (int i = 0; i < N; i++)
	{
		pi += (1.0 / pow(16, i)) * ((4.0 / (8.0 * i + 1)) 
			- (2.0 / (8.0 * i + 4)) - (1.0 / (8.0 * i + 5)) 
			- (1.0 / (8.0 * i + 6)));
	}
	return pi;
}

double formula_Bailey_Borwein_Plouffe_with_OPENMP(int N)
{
	double pi = 0;
	#pragma omp parallel for reduction(+:pi)
	for (int i = 0; i < N; i++)
	{
		pi += (1.0 / pow(16, i)) * ((4.0 / (8.0 * i + 1)) 
			- (2.0 / (8.0 * i + 4)) - (1.0 / (8.0 * i + 5)) 
			- (1.0 / (8.0 * i + 6)));
	}
	return pi;
}

int main()
{
	#ifdef _OPENMP
		printf("_OPENMP Defined\n");
	#else
		printf("_OPENMP UnDefined\n");
	#endif

	int N = 14;
	
	std::map<std::string, double> result_Bailey_Borwein_Plouffed_MAIN_THREAD =
		countTime(N, [](int N) { return formula_Bailey_Borwein_Plouffe(N); });

	std::map<std::string, double> result_Bailey_Borwein_Plouffed_MULTY_THREAD =
		countTime(N, [](int N) { return formula_Bailey_Borwein_Plouffe_with_OPENMP(N); });

	printf("\nBailey Borwein Plouffed MAIN THREAD PI: %.18f", 
		result_Bailey_Borwein_Plouffed_MAIN_THREAD[PI]);
	printf("\nBailey Borwein Plouffed MAIN THREAD time: %.8f s", 
		result_Bailey_Borwein_Plouffed_MAIN_THREAD[TIME]);

	printf("\nBailey Borwein Plouffed MULTY THREAD PI: %.18f", 
		result_Bailey_Borwein_Plouffed_MULTY_THREAD[PI]);
	printf("\nBailey Borwein Plouffed MULTY THREAD time: %.8f s", 
		result_Bailey_Borwein_Plouffed_MULTY_THREAD[TIME]);
}
