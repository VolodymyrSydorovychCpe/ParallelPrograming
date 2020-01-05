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

double formula_Bellard(int N)
{
	double pi = 0;
	for (int i = 0; i < N; i++)
	{
		pi += (pow(-1.0, i) / pow(2.0, i * 10)) * (-(32.0 / (4.0 * i + 1)) 
			- (1.0 / (4.0 * i + 3)) + (256.0 / (10.0 * i + 1)) 
			- (64.0 / (10.0 * i + 3)) - (4.0 / (10.0 * i + 5)) 
			- (4.0 / (10.0 * i + 7)) + (1.0 / (10.0 * i + 9)));
	}
	pi = pi * 1.0 / pow(2.0, 6);
	return pi;
}

double formula_Bailey_Borwein_Plouffe(int N)
{
	double pi = 0;
	for (int i = 0; i < N; i++)
	{
		pi += (1.0 / pow(16, i)) * ((4.0 / (8.0 * i + 1)) - (2.0 / (8.0 * i + 4)) 
			- (1.0 / (8.0 * i + 5)) - (1.0 / (8.0 * i + 6)));
	}
	return pi;
}

double formula_Leybnitz(int N)
{
	double pi = 0;
	for (int i = 1; i <= N; i++)
	{
		pi += 1.0 / ((4.0 * i - 1) * (4.0 * i + 1));
	}
	pi = 4.0 - 8.0 * pi;
	return pi;
}

int main()
{
	int N = 18;

	std::map<std::string, double> result_Bellard = 
		countTime(N, [](int N) { return formula_Bellard(N); });
	std::map<std::string, double> result_Bailey_Borwein_Plouffed = 
		countTime(N, [](int N) { return formula_Bailey_Borwein_Plouffe(N); });
	std::map<std::string, double> result_Leybnitz = 
		countTime(N, [](int N) { return formula_Leybnitz(N); });
	
	printf("PI from proved source: 3.141592653589793238");
	printf("\nBellard PI: %.18f", result_Bellard[PI]);
	printf("\nBailey Borwein Plouffed PI: %.18f", result_Bailey_Borwein_Plouffed[PI]);
	printf("\nLeybnitz PI: %.18f", result_Leybnitz[PI]);

	printf("\n\nBellard  time: %.8f s", result_Bellard[TIME]);
	printf("\nBailey Borwein Plouffed time: %.8f s", result_Bailey_Borwein_Plouffed[TIME]);
	printf("\nLeybnitz time: %.8f s", result_Leybnitz[TIME]);
}
