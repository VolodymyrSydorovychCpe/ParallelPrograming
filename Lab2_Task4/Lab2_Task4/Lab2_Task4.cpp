#include <iostream>
#include <math.h>

void printArray(double* array, int arraySize) {
	std::cout << "{";
	for (int i = 0; i < arraySize; i++) {
		std::cout << array[i];
		if ((arraySize - i) > 1) {
			std::cout << ",";
		}
	}
	std::cout << "}";
}

void roundDataInArray(double* array, int n) {
	for (int i = 0; i < n; i++) {
		double temp = array[i];
		long decimalPart = (long)temp;
		double fractionalPart = temp - decimalPart;
		if (fractionalPart / 0.5 >= 1) {
			array[i] = decimalPart + 1;
		}
		else {
			array[i] = decimalPart;
		}
	}
}

int main()
{
	int const  n1 = 3;
	float* array1 = new float[n1] {-1.2, 0.6, 1.7};
	double* array1_convertedToDouble = new double[n1] {};

	for (int i = 0; i < n1; ++i) { 
		array1_convertedToDouble[i] = (double)array1[i];
	}

	std::cout << "Array before rounding : ";
	printArray(array1_convertedToDouble, n1);
	std::cout << "\n";

	roundDataInArray(array1_convertedToDouble, n1);

	std::cout << "Array after rounding : ";
	printArray(array1_convertedToDouble, n1);
	std::cout << "\n";

	int const  n2 = 3;
	double* array2 = new double[n1] {-1.2, 0.5, 1.8};

	std::cout << "Array before rounding : ";
	printArray(array2, n2);
	std::cout << "\n";

	roundDataInArray(array2, n2);

	std::cout << "Array after rounding : ";
	printArray(array2, n2);
	std::cout << "\n";

}