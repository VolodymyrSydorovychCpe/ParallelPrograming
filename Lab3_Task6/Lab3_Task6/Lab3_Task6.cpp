#include <iostream>
#include <omp.h>
#include <intrin.h>
#include <mmintrin.h>
#include <map>
#include <string.h>
#include <functional>

template  <typename T>
void fillData(T* y, int size) {
	for (int i = 0; i < size; i++) {
		y[i] = rand();
	}
}

template  <typename T>
double countTime(T* x, T* y, int N, std::function<void(T * x, T * y, int N)> function) {
	double start, finish;
	start = omp_get_wtime();
	function(x, y, N);
	finish = omp_get_wtime();
	return finish - start;
}

template  <typename T>
void sqrtY(T* x, T* y, int N)
{
	for (int i = 0; i < N; i++)
	{
		if (typeid(T) == typeid(float))
			x[i] = sqrtf(y[i]);
		if (typeid(T) == typeid(double))
			x[i] = sqrt(y[i]);
	}
}

void sqrtAVX(float* x, const float* y, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		_mm256_storeu_ps(&x[i], _mm256_sqrt_ps(_mm256_loadu_ps(&y[i])));
	}
}

void sqrtAVX(double* x, const double* y, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		_mm256_storeu_pd(&x[i], _mm256_sqrt_pd(_mm256_loadu_pd(&y[i])));
	}
}


int main()
{
	int N = 4096 * 4096;
	float* x_float = new float[N], * y_float = new float[N], * z_float = new float[N];
	double* x_double = new double[N], * y_double = new double[N], * z_double = new double[N];

	fillData(y_float, N);
	fillData(y_double, N);

	printf("\nFloat time: %f s",
		countTime<float>(x_float, y_float, N, [](float* x, float* y, int N) { sqrtY(x, y, N); }));
	printf("\nDouble time: %f s",
		countTime<double>(x_double, y_double, N, [](double* x, double* y, int N) { sqrtY(x, y, N); }));

	printf("\nFloat AVX time: %f s",
		countTime<float>(x_float, y_float, N, [](float* x, float* y, int N) { sqrtAVX(x, y, N); }));
	printf("\nDouble AVX time: %f s",
		countTime<double>(x_double, y_double, N, [](double* x, double* y, int N) { sqrtAVX(x, y, N); }));
}
