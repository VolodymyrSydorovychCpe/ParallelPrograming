#include <iostream>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include <chrono>
#include <intrin.h>

using namespace std::chrono;
using namespace std;

int accuracy_time()
{
	time_t start = time(0), finish = start;
	while (finish == start)
	{
		finish = time(0);
	}
	return finish - start;
}

double accuracy_openmp()
{
	double start = omp_get_wtime(), finish;
	do {
		finish = omp_get_wtime();
	} while (finish - start == 0);
	return finish - start;
}

double accuracy_clock() {
	clock_t Start, Finish;
	Start = clock();
	do {
		Finish = clock();
	} while (Finish - Start == 0);
	return (Finish - Start + 0.) / CLOCKS_PER_SEC;
}

double accuracy_chrono() {
	high_resolution_clock::time_point start = high_resolution_clock::now();
	high_resolution_clock::time_point finish = start;
	while ((finish - start).count() == 0) {
		finish = high_resolution_clock::now();
	};
	duration<double> time_span = duration_cast<duration<double>>(finish - start);
	return time_span.count();
}

double accuracy_GetSystemTimeAsFileTime()
{
	FILETIME start, finish;
	GetSystemTimeAsFileTime(&start);
	do {
		GetSystemTimeAsFileTime(&finish);
	} while (finish.dwLowDateTime == start.dwLowDateTime);
	return (finish.dwLowDateTime - start.dwLowDateTime + 0.) / 10000000;
}

double accuracy_GetSystemTimePreciseAsFileTime() {
	FILETIME systemTimeAsFileTime;
	GetSystemTimePreciseAsFileTime(&systemTimeAsFileTime);
	double start = systemTimeAsFileTime.dwLowDateTime, finish;
	
	do {
		GetSystemTimePreciseAsFileTime(&systemTimeAsFileTime);
		finish = systemTimeAsFileTime.dwLowDateTime;
	} while (finish - start == 0);

	return (finish - start + 0.) / 10000;;
}

double accuracy_GetTickCount() {
	DWORD start = GetTickCount(), finish;
	
	do {
		finish = GetTickCount();
	} while (finish - start == 0);

	return (finish - start + 0.) / 1000;;
}

double accuracy_QueryPerformanceCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	double start = li.LowPart, finish;

	do {
		QueryPerformanceCounter(&li);
		finish = li.LowPart;
	} while (finish - start == 0);

	LARGE_INTEGER liFreq;
	QueryPerformanceFrequency(&liFreq);
	return (finish - start) / liFreq.LowPart;
}

double accuracy_rdtsc() {

	unsigned __int64 start, finish;
	start = __rdtsc();

	do {
		finish = __rdtsc();
	} while (finish - start == 0);

	return (finish - start + 0.);
}

int main() {
	cout << "time accuracy = " << accuracy_time() << "\n";
	cout << "clock accuracy = " << accuracy_clock() << "\n";
	cout << "GetSystemTimeAsFileTime accuracy = " << accuracy_GetSystemTimeAsFileTime() << "\n";
	cout << "GetSystemTimePreciseAsFileTime accuracy = " << accuracy_GetSystemTimePreciseAsFileTime() << "\n";
	cout << "GetTickCount accuracy = " << accuracy_GetTickCount() << "\n";
	cout << "_rdtsc accuracy = " << accuracy_rdtsc() << "\n";
	cout << "QueryPerformanceCounter accuracy = " << accuracy_QueryPerformanceCounter() << "\n";
	cout << "chrono accuracy = " << accuracy_chrono() << "\n";
	cout << "omp_get_wtime accuracy = " << accuracy_openmp() << "\n";
	return 0;
}

