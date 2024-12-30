#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned long long int_l;

inline int_l add(int_l a, int_l b) { return static_cast<int_l>(a + b); }
inline int_l mul(int_l a, int_l b) { return static_cast<int_l>(a * b);; }

template<class T>
ostream& operator<< (ostream& ostream, vector<T> array) {
	ostream << "[ ";
	for (int i = 0; i < array.size(); i++) {
		ostream << array[i] << ", ";
	}
	ostream << "]";

	return ostream;
}

int_l calculate(vector<int_l>& arr, unsigned int operation, int_l trueOperation(int_l, int_l), int_l falseOperation(int_l, int_l)) {
	
	int_l total = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		int_l num = arr[i];

		bool useTrueOperation = operation & 1;
		operation >>= 1;

		if (useTrueOperation) {
			total = trueOperation(total, num);
		} else {
			total = falseOperation(total, num);
		}
	}

	return total;
}


int main() {

	const string filename = "input2.txt";
	ifstream inFile(filename);

	vector<int_l> expectedResults;
	vector<vector<int_l>> parameters;

	string line;
	while (getline(inFile, line)) {
		istringstream lineStream(line);

		int_l temp;
		vector<int_l> params;
		char _;

		lineStream >> temp >> _;
		expectedResults.push_back(temp);

		while(lineStream >> temp){
			params.push_back(temp);
		}
		parameters.push_back(params);
	}

	int_l count = 0;
	for (int i = 0; i < parameters.size(); i++) {
		int_l expectedResult = expectedResults[i];
		auto& array = parameters[i];

		unsigned int oper = pow(2, array.size());
		while(--oper) {
			if (expectedResult == calculate(array, oper, add, mul)) {
				count += expectedResult;
				break;
			}
		}
	}

	cout << count << endl;

	return 0;
}