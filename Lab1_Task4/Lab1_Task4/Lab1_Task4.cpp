#include <iostream>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include <chrono>
#include <intrin.h>

using namespace std::chrono;
using namespace std;

double estimation_for_adding(int arrayToFill[], int arraySize)
{
	double start = omp_get_wtime(), finish;

	for (int i = 0; i < arraySize; i++) {
		arrayToFill[i] = i;
	}

	finish = omp_get_wtime();
	return finish - start;
}

double get_cycle_count(int arrayToFill[], int arraySize) {
	int starts_ms = GetTickCount(), end_ms;
	int timeSec = 0;
	int count = 0;

	while (timeSec < 2) {
		for (int i = 0; i < arraySize; i++) {
			arrayToFill[i] = i;
		}

		end_ms = GetTickCount();
		timeSec = (end_ms - starts_ms) / 1000;
		count++;
	}
	return count;
}


int main() {
	int const ammountToFill1 = 100000;
	int* arrayToFill1 = new int[ammountToFill1];

	int const ammountToFill2 = 200000;
	int* arrayToFill2 = new int[ammountToFill2];

	int const ammountToFill3 = 300000;
	int* arrayToFill3 = new int[ammountToFill3];

	double rdtsc_result_100000 = estimation_for_adding(arrayToFill1, ammountToFill1);
	double rdtsc_result_200000 = estimation_for_adding(arrayToFill2, ammountToFill2);
	double rdtsc_result_300000 = estimation_for_adding(arrayToFill3, ammountToFill3);

	double tickCount_100000_result = get_cycle_count(arrayToFill1, ammountToFill1);
	double tickCount_200000_result = get_cycle_count(arrayToFill2, ammountToFill2);
	double tickCount_300000_result = get_cycle_count(arrayToFill3, ammountToFill3);

	cout << "_rdtsc estimation for adding " << ammountToFill1 << " = " << rdtsc_result_100000 << "\n";
	cout << "_rdtsc estimation for adding " << ammountToFill2 << " = " << rdtsc_result_200000 << "\n";
	cout << "_rdtsc estimation for adding " << ammountToFill3 << " = " << rdtsc_result_300000 << "\n";

	cout << "Absolut time estimation for adding " << ammountToFill1 << " per 2 sec = " << tickCount_100000_result << " cycles \n";
	cout << "Absolut time estimation for adding " << ammountToFill2 << " per 2 sec = " << tickCount_200000_result << " cycles \n";
	cout << "Absolut time estimation for adding " << ammountToFill3 << " per 2 sec = " << tickCount_300000_result << " cycles \n";

	cout << "T(20000)/T(10000) omp: " << rdtsc_result_200000 / rdtsc_result_100000 << "\n";;
	cout << "T(20000)/T(10000) clock: " << tickCount_200000_result / tickCount_100000_result << "\n";

	cout << "T(30000)/T(10000) omp: " << rdtsc_result_300000 / rdtsc_result_100000 << "\n";;
	cout << "T(30000)/T(10000) clock: " << tickCount_300000_result / tickCount_100000_result << "\n";

	return 0;
}
