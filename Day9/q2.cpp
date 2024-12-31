#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string filename = "input2.txt";
const char FREE_SPACE = '.';

int main() {

	vector<int> rawDiskData;
	vector<int> diskData;
	ifstream inFile(filename);

	const int spaceNum = -1;

	int currNum = 0;
	bool isInputSpaceValue = false;
	char inputVal;
	while (inFile) {
		inFile >> inputVal;

		rawDiskData.push_back(inputVal - '0');
		for (int i = 0; i < inputVal - '0'; i++) {
			diskData.push_back(isInputSpaceValue ? spaceNum : currNum);
		}

		currNum += isInputSpaceValue ? 0 : 1;
		isInputSpaceValue = !isInputSpaceValue;
	}

	int freeSpaceIndex = 0, freeSpaceCount = 0;
	int lastNumberIndex = diskData.size() - 1, lastNumberCount = 0;

	while (lastNumberIndex) {
		//cout << "Outer while loop: lastNumberIndex = " << lastNumberIndex << endl;

		lastNumberCount = 0;
		while (diskData[lastNumberIndex] == spaceNum && lastNumberIndex) {
			lastNumberIndex--;
		}
		while(diskData[lastNumberIndex - lastNumberCount] == diskData[lastNumberIndex] && lastNumberIndex - lastNumberCount) {
			lastNumberCount++;
		}

		//cout << "Dealing set of " << diskData[lastNumberIndex] << " " << endl;
		freeSpaceIndex = 0;
		while(freeSpaceIndex < lastNumberIndex - lastNumberCount) {
			freeSpaceCount = 0;
			
			while (diskData[freeSpaceIndex] != spaceNum && freeSpaceIndex < diskData.size() - 1) {
				freeSpaceIndex++;
			}

			while(diskData[freeSpaceIndex + freeSpaceCount] == spaceNum && freeSpaceIndex + freeSpaceCount < diskData.size() - 1) {
				freeSpaceCount++;
			}

			if (freeSpaceIndex > lastNumberIndex - lastNumberCount) {
				break;
			}

			if (freeSpaceCount >= lastNumberCount) {
				int tempCount = 0;
				while (lastNumberCount - tempCount) {
					diskData[freeSpaceIndex + tempCount] = diskData[lastNumberIndex - tempCount];
					diskData[lastNumberIndex - tempCount] = spaceNum;
					tempCount++;
				}

				break;
			} else {
				freeSpaceIndex += freeSpaceCount;
			}
		}

		lastNumberIndex -= lastNumberCount;

		// for (int i = 0; i < diskData.size(); i++) {
		// 	if (diskData[i] == spaceNum) cout << ".";
		// 	else cout << diskData[i];
		// }
		// cout << endl;
	}


	unsigned long long int count = 0;
	for (int i = 0; i < diskData.size(); i++) {
		count += i * (diskData[i] == spaceNum ? 0 : diskData[i]);
	}
	
	cout << count << endl;

	return 0;
}
