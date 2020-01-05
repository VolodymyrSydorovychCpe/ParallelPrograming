#include <iostream>

int countPositiveNumbers(int* array, int arraySize) {
	int positiveDigitCount = 0;
	for (int i = 0; i < arraySize; i++) {
		if (array[i] >= 0) {
			positiveDigitCount++;
		}
	}
	return positiveDigitCount;
}

int main()
{
	int const  n = 7;
	int* array = new int[n] {-2, 3, 1, 8, -4, -7, 4};
    std::cout << "Array has " << countPositiveNumbers(array, n) << " positive numbers";
}
