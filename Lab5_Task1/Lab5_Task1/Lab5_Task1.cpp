#include <iostream>
#include <omp.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>

std::string const ORDERED_FILE_NAME = "d://OrderedKeys.txt";
std::string const NOT_ORDERED_FILE_NAME = "d://NonOrderedKeys.txt";
std::string const RESULT_FILE_NAME = "d://result.txt";

double countTime(std::string* keys, int N, std::function<void(std::string* x, int N)> function) {
	double start = omp_get_wtime();
	function(keys, N);
	double finish = omp_get_wtime();
	return finish - start;
}

void writeToFile(std::string fileName, std::string* keys, int keySize) {
	std::ofstream file(fileName);
	file << keySize << std::endl;
	for (int i = 0; i < keySize; i++)
	{
		file << keys[i] << std::endl;
	}
	file.close();
}

void check(std::string* keys, int n) {
	std::ifstream notOrderedKeysFile(NOT_ORDERED_FILE_NAME);
	std::ofstream resultFile(RESULT_FILE_NAME);

	std::string keyArraySizeString;
	std::getline(notOrderedKeysFile, keyArraySizeString);

#pragma omp parallel for 
	for (int i = 0; i < std::stoi(keyArraySizeString); i++)
	{
		std::string line;
		std::getline(notOrderedKeysFile, line);

		bool found = false;
		int indexOfFoundKey = -1;
		for (int k = 0; k < n && indexOfFoundKey < 0; k++)
		{
#pragma omp critical
			indexOfFoundKey = (line == keys[k]) ? k : -1;
		}
#pragma omp critical
		resultFile << line 
			<< (indexOfFoundKey >= 0 ? " found at index " + std::to_string(indexOfFoundKey) : " not found ") 
			<< std::endl;
	}

	notOrderedKeysFile.close();
	resultFile.close();
}

void checkParallel(std::string* keys, int n) {
	std::ifstream notOrderedKeysFile(NOT_ORDERED_FILE_NAME);
	std::ofstream resultFile(RESULT_FILE_NAME);

	std::string keyArraySizeString;
	std::getline(notOrderedKeysFile, keyArraySizeString);

	for (int i = 0; i < std::stoi(keyArraySizeString); i++)
	{
		std::string line;
		std::getline(notOrderedKeysFile, line);

		bool found = false;
		int indexOfFoundKey = -1;
		for (int k = 0; k < n && indexOfFoundKey < 0; k++)
		{
			indexOfFoundKey = (line == keys[k]) ? k : -1;
		}
		resultFile << line
			<< (indexOfFoundKey >= 0 ? " found at index " + std::to_string(indexOfFoundKey) : " not found ")
			<< std::endl;
	}

	notOrderedKeysFile.close();
	resultFile.close();
}

void prepareData() {
	int notSortedKeyArraySize = 1000000;
	int sortedKeyArraySize = 100;
	std::string* notSortedKeys = new std::string[notSortedKeyArraySize];
	std::string* sortedKeys = new std::string[sortedKeyArraySize];

	char* c = new char();

	for (int i = 0; i < notSortedKeyArraySize; i++)
	{
		for (int k = 0; k < 15; k++)
		{
			c[k] = 'A' + rand() % 24;
		}
		if (i < sortedKeyArraySize) {
			sortedKeys[i] = c;
		}
		notSortedKeys[i] = c;
	}
	sort(sortedKeys, sortedKeys + sizeof(&sortedKeys) / sizeof(sortedKeys[0]));

	writeToFile(NOT_ORDERED_FILE_NAME, notSortedKeys, notSortedKeyArraySize);
	writeToFile(ORDERED_FILE_NAME, sortedKeys, sortedKeyArraySize);
}

int main()
{
	prepareData();

	std::ifstream orderedKeysFile(ORDERED_FILE_NAME);

	std::string keyArraySizeString;
	std::getline(orderedKeysFile, keyArraySizeString);
	int keyArraySize = std::stoi(keyArraySizeString);

	std::string* keys = new std::string[keyArraySize];

	for (int i = 0; i < keyArraySize; i++) {
		std::string key; 
		std::getline(orderedKeysFile, key);
		keys[i] = key;
	}
	orderedKeysFile.close();
	
	printf("\nMain thread time: %f s", 
		countTime(keys, keyArraySize, [](std::string* keys, int N) { check(keys, N); }));
	printf("\nMultiple threads time: %f s", 
		countTime(keys, keyArraySize, [](std::string* keys, int N) { checkParallel(keys, N); }));
}
