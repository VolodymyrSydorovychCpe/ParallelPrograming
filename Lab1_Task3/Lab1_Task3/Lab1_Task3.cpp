#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

double estimate_by_QueryPerformanceCounter(int arrayToFill [], int arraySize) {

	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	double start = li.LowPart, finish;

	for (int i = 0; i < arraySize; i++) {
		arrayToFill[i] = i;
	}

	LARGE_INTEGER li1;
	QueryPerformanceCounter(&li1);
	finish = li1.LowPart;

	LARGE_INTEGER liFreq;
	QueryPerformanceFrequency(&liFreq);

	return (finish - start) / liFreq.LowPart;
}

double estimate_by_rdtsc(int arrayToFill[], int arraySize) {

	unsigned __int64 start, finish;
	start = __rdtsc();

	for (int i = 0; i < arraySize; i++) {
		arrayToFill[i] = i;
	}

	finish = __rdtsc();

	return finish - start;
}


int main() {

	int ammountToFill1 = 1000;
	int arrayToFill1 [1000];

	int ammountToFill2 = 1000;
	int arrayToFill2 [1000];

	cout << "_rdtsc estimation = " << estimate_by_rdtsc(arrayToFill1, 1000) << "\n";
	cout << "QueryPerformanceCounter estimation = " << estimate_by_QueryPerformanceCounter(arrayToFill2, 1000) << "\n";
	return 0;
}

