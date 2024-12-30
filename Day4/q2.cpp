#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int checkXMAS(const vector<vector<char>>& matrix, int row, int col) {
	int count = 0;
	
	if (col >= 0 && col <= matrix[0].size() - 4) {
		if (matrix[row][col] == 'X' && matrix[row][col + 1] == 'M' && matrix[row][col + 2] == 'A' && matrix[row][col + 3] == 'S') {
			count++;
		} else if (matrix[row][col] == 'S' && matrix[row][col + 1] == 'A' && matrix[row][col + 2] == 'M' && matrix[row][col + 3] == 'X') {
			count++;
		}
	} 
	if (row >= 0 && row <= matrix[0].size() - 4) {
		if (matrix[row][col] == 'X' && matrix[row + 1][col] == 'M' && matrix[row + 2][col] == 'A' && matrix[row + 3][col] == 'S') {
			count++;
		} else if (matrix[row][col] == 'S' && matrix[row + 1][col] == 'A' && matrix[row + 2][col] == 'M' && matrix[row + 3][col] == 'X') {
			count++;
		}
	}
	if ((row >= 0 && row <= matrix[0].size() - 4) && (col >= 0 && col <= matrix[0].size() - 4)) {
		if (matrix[row][col] == 'X' && matrix[row + 1][col + 1] == 'M' && matrix[row + 2][col + 2] == 'A' && matrix[row + 3][col + 3] == 'S') {
			count++;
		} else if (matrix[row][col] == 'S' && matrix[row + 1][col + 1] == 'A' && matrix[row + 2][col + 2] == 'M' && matrix[row + 3][col + 3] == 'X') {
			count++;
		}
	}
	if ((row >= 0 && row <= matrix[0].size() - 4) && (col >= 3 && col <= matrix[0].size() - 1)) {
		if (matrix[row][col] == 'X' && matrix[row + 1][col - 1] == 'M' && matrix[row + 2][col - 2] == 'A' && matrix[row + 3][col - 3] == 'S') {
			count++;
		} else if (matrix[row][col] == 'S' && matrix[row + 1][col - 1] == 'A' && matrix[row + 2][col - 2] == 'M' && matrix[row + 3][col - 3] == 'X') {
			count++;
		}
	}

	return count;
}

int checkX_MAS(const vector<vector<char>>& matrix, int row, int col) {
	if (matrix[row][col] == 'A' && (row >= 1 && row <= matrix.size() - 2 && col >= 1 && col <= matrix[0].size() - 2)) {
		if (matrix[row - 1][col - 1] + matrix[row + 1][col + 1] == 'M' + 'S' && matrix[row - 1][col + 1] + matrix[row + 1][col - 1] == 'M' + 'S') {
			return 1;
		}
	}

	return 0;
}


int main() {

	string inFileName = "input2.txt";
	ifstream inFile(inFileName);

	// Check if file is open
	if (!inFile.is_open()) {
		cerr << "Error opening file for reading: " << inFileName << endl;
		return 1;
	}

	// Read matrix from file
	vector<vector<char>> matrix;
	string line;
	getline(inFile, line);
	while (!inFile.eof()) {
		vector<char> row;
		for (char c : line) {
			row.push_back(c);
		}
		matrix.push_back(row);
		getline(inFile, line);
	}

	inFile.close();
	int count = 0;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			count += checkX_MAS(matrix, i, j);
		}
	}

	cout << "Count: " << count << endl;

	return 0;
}