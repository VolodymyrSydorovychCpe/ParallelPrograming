#include <iostream>
#include <omp.h>
#include <Windows.h>

typedef struct Params
{
	double pi;
	int i;
	int threads;
	int N;
} ThreadParams, * PThreadParams;


double formula_Bailey_Borwein_Plouffe(int N)
{
	double pi = 0;
	for (int i = 0; i < N; i++) {
		pi += (1.0 / pow(16, i)) * ((4.0 / (8.0 * i + 1)) - (2.0 / (8.0 * i + 4))
			- (1.0 / (8.0 * i + 5)) - (1.0 / (8.0 * i + 6)));
		}
	return pi;
}


DWORD WINAPI formula_Bailey_Borwein_Plouffe_multy_threaded(LPVOID lpParam)
{
	PThreadParams mp = (PThreadParams)lpParam;
	int k = mp->i, N = mp->N, threads = mp->threads;

	for (int i = k * threads; i < i + threads && i < N; i++)
	{
		mp->pi += (1.0 / pow(16, i)) * ((4.0 / (8.0 * i + 1)) 
			- (2.0 / (8.0 * i + 4)) - (1.0 / (8.0 * i + 5)) - (1.0 / (8.0 * i + 6)));
	}
	return 0;
}

int main()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	const int MAX_THREADS = si.dwNumberOfProcessors;
	
	int numberOfIterations = 14;
	PThreadParams* mp = new PThreadParams[MAX_THREADS]{};
	DWORD* dwThreadIdArray = new DWORD[MAX_THREADS];
	HANDLE* hThreadArray = new HANDLE[MAX_THREADS];

	double* pi = new double(0);

	for (int i = 0; i < MAX_THREADS && i < numberOfIterations; i++)
	{
		mp[i] = (PThreadParams)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ThreadParams));

		mp[i]->i = i;
		mp[i]->pi = 0;
		mp[i]->threads = MAX_THREADS;
		mp[i]->N = numberOfIterations;

		hThreadArray[i] = 
			CreateThread(NULL, 0, formula_Bailey_Borwein_Plouffe_multy_threaded, 
				mp[i], 0, &dwThreadIdArray[i]);
	}

	double start_time_multy_thread = omp_get_wtime();
	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	for (int k = 0; k < MAX_THREADS && k < numberOfIterations; k++)
	{
		*pi += mp[k]->pi;
		CloseHandle(hThreadArray[k]);
	}
	double multy_thread_time_result = omp_get_wtime() - start_time_multy_thread;


	double start_time_main_thread = omp_get_wtime();
	double pi_main_thread_result = formula_Bailey_Borwein_Plouffe(numberOfIterations);
	double main_thread_time_result = omp_get_wtime() - start_time_main_thread;

	printf("MULTY THREAD PI %.14f", *pi);
	printf("\nMAIN THREAD PI %.14f", pi_main_thread_result);
	printf("\nMULTY THREAD time: %.14f s", multy_thread_time_result);
	printf("\nMAIN THREAD time: %.14f s", main_thread_time_result);
}
