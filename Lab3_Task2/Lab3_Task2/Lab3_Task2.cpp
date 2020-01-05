#include <iostream>
#include <omp.h>
#include <intrin.h>
#include <mmintrin.h>
#include <map>
#include <string.h>
#include <functional>

template  <typename T>
void sum(T* x, T* y, T* z, int n)
{
	for (int i = 0; i < n; i++)
	{
		x[i] = abs(y[i] + z[i]);
	}
}

template  <typename T>
void sumSSE(T* x, T* y, T* z, int size, int intLenght)
{
	for (int i = 0; i < size; i ++)
	{
		__m128i x__m128i = _mm_loadu_si128((__m128i*) & y[i]);
		__m128i y__m128i = _mm_loadu_si128((__m128i*) & z[i]);

		if (intLenght == 8) {
			x[i] = (T)&_mm_abs_epi8(_mm_add_epi8(x__m128i, y__m128i));
		}
		if (intLenght == 16) {
			x[i] = (T)_mm_abs_epi16(_mm_add_epi16(x__m128i, y__m128i));
		}
		if (intLenght == 32) {
			x[i] = (T)_mm_abs_epi32(_mm_add_epi32(x__m128i, y__m128i));
		}
		if (intLenght == 64) {
			x[i] = (T)_mm_abs_epi64(_mm_add_epi64(x__m128i, y__m128i));
		}
	}

}

template  <typename T>
void sumAVX(T* x, T* y, T* z, int Size, int intLength)
{
	for (int i = 0; i < Size; i ++)
	{
		__m256i x__m256i = _mm256_loadu_si256((__m256i*)&y[i]);
		__m256i y__m256i = _mm256_loadu_si256((__m256i*)&z[i]);

		if (intLength == 8) {
			x[i] = (T)&_mm256_abs_epi8(_mm256_add_epi8(x__m256i, y__m256i));
		}
		if (intLength == 16) {
			x[i] = (T)&_mm256_abs_epi16(_mm256_add_epi16(x__m256i, y__m256i));
		}
		if (intLength == 32) {
			x[i] = (T)&_mm256_abs_epi32(_mm256_add_epi32(x__m256i, y__m256i));
		}
		if (intLength == 64) {
			//x[i] = (T)&_mm256_abs_epi64(_mm256_add_epi64(x__m256i, y__m256i));
		}
	}

}

void sumAVX(float* x, float* y, float* z, int size)
{
	for (int i = 0; i < size; i ++)
	{
		_mm256_storeu_ps(&x[i], _mm256_add_ps(_mm256_loadu_ps(&y[i]), _mm256_loadu_ps(&z[i])));
	}
}

void sumAVX(double* x, double* y, double* z, int size)
{
	for (int i = 0; i < size; i ++)
	{
		_mm256_storeu_pd(&x[i], _mm256_add_pd(_mm256_loadu_pd(&y[i]), _mm256_loadu_pd(&z[i])));
	}
}

template  <typename T>
void fillData(T* y, T* z, int size) {
	for (int i = 0; i < size; i++) {
		y[i] = rand();
		z[i] = rand();
	}
}

template  <typename T>
double countTime(T* x, T* y, T* z, int N, std::function<void(T * x, T * y, T * z, int N)> function) {
	double start, finish;
	start = omp_get_wtime();
	function(x, y, z, N);
	finish = omp_get_wtime();
	return finish - start;
}

template  <typename T>
double countTime(T* x, T* y, T* z, int N, int mode, std::function<void(T * x, T * y, T * z, int N, int mode)> function) {
	double start = omp_get_wtime();
	function(x, y, z, N, mode);
	double finish = omp_get_wtime();
	return finish - start;
}


int main()
{
	int N = 4096 * 4096;
	__int8* x__int8 = new __int8[N], * y__int8 = new __int8[N], * z__int8 = new __int8[N] {};
	__int16* x__int16 = new __int16[N], * y__int16 = new __int16[N], * z__int16 = new __int16[N];
	__int32* x__int32 = new __int32[N], * y__int32 = new __int32[N], * z__int32 = new __int32[N];
	__int64* x__int64 = new __int64[N], * y__int64 = new __int64[N], * z__int64 = new __int64[N];
	float* x_float = new float[N], * y_float = new float[N], * z_float = new float[N];
	double* x_double = new double[N], * y_double = new double[N], * z_double = new double[N];
	
	fillData(y__int8, z__int8, N);
	fillData(y__int16, z__int16, N);
	fillData(y__int32, z__int32, N);
	fillData(y__int64, z__int64, N);
	fillData(y_float, z_float, N);
	fillData(y_double, z_double, N);
	
	printf("\nInt8 time: %f s", 
		countTime<__int8>(x__int8, y__int8, z__int8, N, [](__int8* x, __int8* y, __int8* z, int N) { sum<__int8>(x, y, z, N); }));
	printf("\nInt16 time: %f s", 
		countTime<__int16>(x__int16, y__int16, z__int16, N, [](__int16* x, __int16* y, __int16* z, int N) { sum<__int16>(x, y, z, N); }));
	printf("\nInt32 time: %f s", 
		countTime<__int32>(x__int32, y__int32, z__int32, N, [](__int32* x, __int32* y, __int32* z, int N) { sum<__int32>(x, y, z, N); }));
	printf("\nInt64 time: %f s", 
		countTime<__int64>(x__int64, y__int64, z__int64, N, [](__int64* x, __int64* y, __int64* z, int N) { sum<__int64>(x, y, z, N); }));
	printf("\nFloat time: %f s", 
		countTime<float>(x_float, y_float, z_float, N, [](float* x, float* y, float* z, int N) { sum<float>(x, y, z, N); }));
	printf("\nDouble time: %f s", 
		countTime<double>(x_double, y_double, z_double, N, [](double* x, double* y, double* z, int N) { sum<double>(x, y, z, N); }));

	printf("\nInt8 AVX time: %f s", 
		countTime<__int8>(x__int8, y__int8, z__int8, N, 8, [](__int8* x, __int8* y, __int8* z, int N, int mode) { sumAVX<__int8>(x, y, z, N, mode); }));
	printf("\nInt16 AVX time: %f s", 
		countTime<__int16>(x__int16, y__int16, z__int16, N, 16, [](__int16* x, __int16* y, __int16* z, int N, int mode) { sumAVX<__int16>(x, y, z, N, mode); }));
	printf("\nInt32 AVX time: %f s", 
		countTime<__int32>(x__int32, y__int32, z__int32, N, 32, [](__int32* x, __int32* y, __int32* z, int N, int mode) { sumAVX<__int32>(x, y, z, N, mode); }));
	printf("\nInt64 AVX time: %f s", 
		countTime<__int64>(x__int64, y__int64, z__int64, N, 64, [](__int64* x, __int64* y, __int64* z, int N, int mode) { sumAVX<__int64>(x, y, z, N, mode); }));
	printf("\nFloat AVX time: %f s",
		countTime<float>(x_float, y_float, z_float, N, [](float* x, float* y, float* z, int N) { sumAVX(x, y, z, N); }));
	printf("\nDouble AVX time: %f s",
		countTime<double>(x_double, y_double, z_double, N, [](double* x, double* y, double* z, int N) { sumAVX(x, y, z, N); }));
}
