#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned long long int_l;

inline int_l add(int_l a, int_l b) { return static_cast<int_l>(a + b); }
inline int_l mul(int_l a, int_l b) { return static_cast<int_l>(a * b); }
inline int_l join(int_l a, int_l b) {
	return static_cast<int_l>(stoull(to_string(a) + to_string(b)));
}

template<class T>
ostream& operator<< (ostream& ostream, vector<T> array) {
	ostream << "[ ";
	for (int i = 0; i < array.size(); i++) {
		ostream << array[i] << ", ";
	}
	ostream << "]";

	return ostream;
}

int_l calculate(vector<int_l>& arr, vector<int> operation, int_l operation_0(int_l, int_l), int_l operation_1(int_l, int_l), int_l operation_2(int_l, int_l)) {
	
	int_l total = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		int_l num = arr[i];

		int operationNum = operation[i];

		switch (operationNum)
		{
		case 0:
			total = operation_0(total, num);
			break;
		case 1:
			total = operation_1(total, num);
			break;
		case 2:
			total = operation_2(total, num);
			break;
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

		vector<int> operation(array.size(), 2);
		bool notDone = true;
		while(notDone) {
			//cout << operation << endl;;
			if (expectedResult == calculate(array, operation, join, add, mul)) {
				count += expectedResult;
				break;
			}

			int updatingIndex = 0;
			while (true) {
				if (updatingIndex == operation.size()) {
					notDone = false;
					break;
				}

				operation[updatingIndex] -= 1;
				if (operation[updatingIndex] < 0) {
					operation[updatingIndex] = 2;
					updatingIndex += 1;
				} else {
					break;
				}
			}
		}
	}

	cout << count << endl;

	return 0;
}