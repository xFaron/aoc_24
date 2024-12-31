#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string filename = "input2.txt";
const char FREE_SPACE = '.';

int main() {

	vector<int> rawDistData;
	vector<int> diskData;
	ifstream inFile(filename);

	const int spaceNum = -1;

	int currNum = 0;
	bool isInputSpaceValue = false;
	char inputVal;
	while (inFile) {
		inFile >> inputVal;

		for (int i = 0; i < inputVal - '0'; i++) {
			diskData.push_back(isInputSpaceValue ? spaceNum : currNum);
		}

		currNum += isInputSpaceValue ? 0 : 1;
		isInputSpaceValue = !isInputSpaceValue;
	}

	int freeSpaceIndex = 0;
	int lastNumberIndex = diskData.size() - 1;

	while (freeSpaceIndex < lastNumberIndex) {
		while (diskData[freeSpaceIndex] != spaceNum) {
			freeSpaceIndex++;
		}

		while (diskData[lastNumberIndex] == spaceNum) {
			lastNumberIndex--;
		}

		if (freeSpaceIndex >= lastNumberIndex) {
			break;
		}

		diskData[freeSpaceIndex] = diskData[lastNumberIndex];
		diskData[lastNumberIndex] = spaceNum;
	}

	// Print array

	// for (int i = 0; i < diskData.size(); i++) {
	// 	cout << diskData[i] << " ";
	// }

	unsigned long long int count = 0;
	for (int i = 0; i < diskData.size(); i++) {
		count += i * (diskData[i] == spaceNum ? 0 : diskData[i]);
	}
	
	cout << count << endl;

	return 0;
}













// string repeatChar(const char& c, const int& n) {
// 	string result = "";
// 	for (int i = 0; i < n; i++) {
// 		result += c;
// 	}
// 	return result;
// }

// string& decodeDiskData(const string& filename, string& diskData) {
// 	// Getting data
// 	ifstream inFile(filename);

// 	char number = '0', space = FREE_SPACE;
// 	char number_count, space_count;
// 	while (inFile) {
// 		inFile >> number_count >> space_count;

// 		for (int i = 0; i < number_count - '0'; i++) {
// 			diskData += number;
// 		}
// 		for (int i = 0; i < space_count - '0'; i++) {
// 			diskData += space;
// 		}

// 		number++;
// 	}

// 	return diskData;
// }