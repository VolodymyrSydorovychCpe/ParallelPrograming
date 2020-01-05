#include <iostream>
#include <omp.h>
using namespace std;

const int n = 1024;

int fillMatrix(int* matrix[n])
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

long multiplyMatrixs(int* matrix1[n], int* matrix2[n], int* result[n]) {
	int y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0, sum = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				sum += matrix1[i][j] * matrix2[j][k];
				y++;
			}
			result[i][k] = sum;
			sum = 0;
		}
	}
	return y;
}

class MatrixUtil {
public: long multiplyMatrixs(int* matrix1[], int* matrix2[], int* result[]) {
	int y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int k = 0, sum = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				sum += matrix1[i][j] * matrix2[j][k];
				y++;
			}
			result[i][k] = sum;
			sum = 0;
		}
	}
	return y;
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
	int* Matrix_1_pointer_without_object[n];
	int* Matrix_2_pointer_without_object[n];
	int* Matrix_3_pointer_without_object[n];

	for (int i = 0; i < n; i++)
	{
		Matrix_1_pointer_without_object[i] = new int[n] {};
		Matrix_2_pointer_without_object[i] = new int[n] {};
		Matrix_3_pointer_without_object[i] = new int[n] {};
	}

	fillMatrix(Matrix_1_pointer_without_object);
	fillMatrix(Matrix_2_pointer_without_object);

	double startTime1 = omp_get_wtime(), finishTime1, result1;

	long complexity1 = multiplyMatrixs(Matrix_1_pointer_without_object, Matrix_2_pointer_without_object, Matrix_3_pointer_without_object);

	finishTime1 = omp_get_wtime();

	cout << "O(n^3) for matrix " << n << " multiplying without object creation by experiment: " << complexity1 << "\n";
	cout << "O(n^3) for matrix " << n << " multiplying without object creation by formula: " << pow(n, 3) << "\n";
	cout << "Spent time for matrix " << n << " multiplying without object creation: " << finishTime1 - startTime1 << "\n";
	
	int* Matrix_1_pointer[n];
	int* Matrix_2_pointer[n];
	int* Matrix_3_pointer[n];

	for (int i = 0; i < n; i++)
	{
		Matrix_1_pointer[i] = new int[n] {};
		Matrix_2_pointer[i] = new int[n] {};
		Matrix_3_pointer[i] = new int[n] {};
	}

	MatrixUtil matrixUtil;
	matrixUtil.fillMatrix(Matrix_1_pointer);
	matrixUtil.fillMatrix(Matrix_2_pointer);

	double startTime2 = omp_get_wtime(), finishTime2, result2;

	long complexity2 = matrixUtil.multiplyMatrixs(Matrix_1_pointer, Matrix_2_pointer, Matrix_3_pointer);

	finishTime2 = omp_get_wtime();
	result2 = finishTime2 - startTime2;

	cout << "O(n^3) for matrix " << n << " multiplying with object creation by experiment: " << complexity2 << "\n";
	cout << "O(n^3) for matrix " << n << " multiplying with object creation by formula: " << pow(n, 3) << "\n";
	cout << "Spent time for matrix " << n << " multiplying with object creation: " << finishTime2 - startTime2 << "\n";

	return 0;
}