#include <iostream>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include <chrono>
#include <intrin.h>

using namespace std;

const int n = 100;

int fillMatrix(int matrix[n][n]) 
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = i * 2 + j * 1 + 1;
		}
	}
	return 0;
}

int multiplyMatrixs(int matrix1[n][n], int matrix2[n][n], int result[n][n]) {
	for (int i = 0; i < n; i++)
	{
		for (int k = 0, sum = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				sum += matrix1[i][j] * matrix2[j][k];
			}
			result[i][k] = sum;
			sum = 0;
		}
	}
	return 0;
}

class MatrixUtil {
	public: void multiplyMatrixs(int* matrix1[], int* matrix2[], int* result[]) {
		for (int i = 0; i < n; i++)
		{
			for (int k = 0, sum = 0; k < n; k++)
			{
				for (int j = 0; j < n; j++)
				{
					sum += matrix1[i][j] * matrix2[j][k];
				}
				result[i][k] = sum;
				sum = 0;
			}
		}
	}

	public: void fillMatrix(int* matrix[]) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = i * 2 + j * 1 + 1;
			}
		}
	}
};

int main()
{
	int matrix1[n][n];
	int matrix2[n][n];
	int matrix3[n][n];

	fillMatrix(matrix1);
	fillMatrix(matrix2);

	__int64 StartTicks1, EndTicks1;

	QueryPerformanceCounter((LARGE_INTEGER*)&StartTicks1);

	multiplyMatrixs(matrix1, matrix2, matrix3);

	QueryPerformanceCounter((LARGE_INTEGER*)&EndTicks1);

	cout << "Spent time for matrix multiplying without object creation: " << EndTicks1 - StartTicks1 << " cycles \n";

	int Matrix_for_object_approach_1[n][n];
	int Matrix_for_object_approach_2[n][n];
	int Matrix_for_object_approach_3[n][n];

	int* Matrix_1_pointer[n];
	int* Matrix_2_pointer[n];
	int* Matrix_3_pointer[n];

	for (int i = 0; i < n; i++)
	{
		Matrix_1_pointer[i] = Matrix_for_object_approach_1[i];
		Matrix_2_pointer[i] = Matrix_for_object_approach_2[i];
		Matrix_3_pointer[i] = Matrix_for_object_approach_3[i];
	}

	MatrixUtil matrixUtil;
	matrixUtil.fillMatrix(Matrix_1_pointer);
	matrixUtil.fillMatrix(Matrix_2_pointer);

	__int64 StartTicks2, EndTicks2;
	QueryPerformanceCounter((LARGE_INTEGER*)&StartTicks2);

	matrixUtil.multiplyMatrixs(Matrix_1_pointer, Matrix_2_pointer, Matrix_3_pointer);
	
	QueryPerformanceCounter((LARGE_INTEGER*)&EndTicks2);

	cout << "Spent time for matrix multiplying with object creation: " << EndTicks2 - StartTicks2 << " cycles \n";

	return 0;
}