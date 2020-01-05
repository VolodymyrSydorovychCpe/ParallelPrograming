#include <iostream>

void sortArray (int* array, int arraySize) {
	for (int y = 0; y < arraySize; y++) {
		for (int i = 1; i < arraySize; i++) {
			if (array[i] < array[i - 1]) {
				int temp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = temp;
			}
		}
	}
}

void printArray(int* array, int arraySize) {
	std::cout << "{";
	for (int i = 0; i < arraySize; i++) {
		std::cout << array[i];
		if ((arraySize - i) > 1) {
			std::cout << ",";
		}
	}
	std::cout << "}";
}

int main()
{
	int const  n = 7;
	int* array = new int[n] {-2, 3, 1, 8, -4, -7, 4};
	std::cout << "Array before sorting: ";
	printArray(array, n);
	sortArray(array, n);
	std::cout << "\nSorted array: ";
	printArray(array, n);
}
