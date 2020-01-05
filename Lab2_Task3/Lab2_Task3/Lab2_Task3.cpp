#include <iostream>
#include <map>
#include <list> 
#include <iterator> 

void multiplyPolinoms(int* coefForPolinom1, int n1, int* coefForPolinom2, int n2) {
	std::map<int, std::list <int>> resultMatrix;	

	int xPow = (n1 - 1) * (n2 - 1);
	xPow--;
	for (int i2 = 0; i2 < n2; i2++) {
		int currentPow2 = n2 - i2;
		for (int i1 = 0; i1 < n1; i1++) {
			int currentPow1 = n1 - i1;
			int currenResultPow = currentPow1 - 1 + currentPow2 - 1;
			resultMatrix[currenResultPow].push_back(coefForPolinom1[i1] * coefForPolinom2[i2]);
		}
	}
	
	for (int i = n2 + n1 - 2; i >= 0; i --) {
		std::list <int> currentList = resultMatrix[i];
		std::list <int> ::iterator it;
		int sum = 0;
		for (it = currentList.begin(); it != currentList.end(); ++it) {
			sum += *it;
		}
		if (sum != 0) {
			if (sum > 0 && i != n2 + n1 - 2) {
				std::cout << "+";
			}
			if (sum != 1) {
				std::cout << sum;
			}
			if (i > 0) {
				std::cout << "x^" << i;
			}
		}
	}
}

int main()
{
	int const  n1 = 3;
	int* coefForPolinom1 = new int[n1] {-1, 0, 1};

	int const  n2 = 3;
	int* coefForPolinom2 = new int[n2] {2, -3, 2};

	int* coefForPolinom1_prepared = new int[n1 + 1] {0, 0, 0, 0};
	coefForPolinom1_prepared[0] = 1;
	for (int i = 1; i < n1 + 1; i++) {
		coefForPolinom1_prepared[i] = coefForPolinom1[i -1];
	}

	int* coefForPolinom2_prepared = new int[n2 + 1] { 0, 0, 0, 0 };
	coefForPolinom2_prepared[0] = 1;
	for (int i = 1; i < n2 + 1; i++) {
		coefForPolinom2_prepared[i] = coefForPolinom2[i - 1];
	}


	multiplyPolinoms(coefForPolinom1_prepared, n1 + 1, coefForPolinom2_prepared, n2 + 1);
}