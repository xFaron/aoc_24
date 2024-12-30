#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const char BLANK_CHAR = '.';

using namespace std;

class Vec2D {
public:
	int x;
	int y;

	Vec2D() : x(0), y(0) {}
	Vec2D(int xC, int yC) : x(xC), y(yC) {}

	friend ostream& operator<< (ostream& outStream, const Vec2D& vec) {
		outStream << "(" << vec.x << ", " << vec.y << ")"; 
		return outStream;
	}

	friend bool operator== (const Vec2D& vec1, const Vec2D& vec2) {
		if (vec1.x == vec2.x && vec1.y == vec2.y) {
			return true;
		}
		return false;
	}

	friend bool operator!= (const Vec2D& vec1, const Vec2D& vec2) {
		if (vec1.x != vec2.x || vec1.y != vec2.y) {
			return true;
		}
		return false;
	}

	friend Vec2D operator+ (Vec2D pos1, const Vec2D pos2) {
		pos1.x += pos2.x;
		pos1.y += pos2.y;

		return pos1;
	}

	friend Vec2D operator- (Vec2D pos1, const Vec2D pos2) {
		pos1.x -= pos2.x;
		pos1.y -= pos2.y;

		return pos1;
	}

	friend Vec2D operator* (Vec2D pos1, const int num) {
		pos1.x *= num;
		pos1.y *= num;

		return pos1;
	}
};

class Map {
private:
	vector<vector<char>> matrix;

public:
	Map(vector<vector<char>> map) {
		matrix = map;
	}

	int rowsLen() const { return matrix.size(); }
	int colsLen() const { return matrix[0].size(); }

	char at(const int x, const int y) const {
		return matrix[y][x];
	}

	char at(const Vec2D& vec) const {
		return matrix[vec.y][vec.x];
	}

	void change(const int x, const int y, char temp) {
		matrix[y][x] = temp;
	}

	void change(const Vec2D& vec, char temp) {
		matrix[vec.y][vec.x] = temp;
	}

	friend ostream& operator<< (ostream& outStream, const Map& map) {
		for (int y = 0; y < map.rowsLen(); y++) {
			for (int x = 0; x < map.colsLen(); x++) {
				outStream << " " << map.at(x, y);
			}
			outStream << "\n";
		}
		return outStream;
	}
};

vector<vector<char>>& getInput(const string filename, vector<vector<char>>& matrix) {
	ifstream inFile(filename);

	if (!inFile) {
		cerr << "Unable to open : " << filename << "\n";
		return matrix;
	}

	string line;
	while (getline(inFile, line)) {
		istringstream lineStream(line);
		vector<char> row;

		char temp;
		while (lineStream >> temp) {
			row.push_back(temp);
		}

		matrix.push_back(row);
	}

	return matrix;
}

bool isInMap(const Map& map, const Vec2D& position) {
	if (position.x >= 0 && position.x < map.colsLen() && position.y >= 0 && position.y < map.rowsLen()) {
		return true;
	}
	return false;
}

int main() {

	string filename = "input2.txt";

	vector<vector<char>> matrix;
	getInput(filename, matrix);

	Map map(matrix);

	vector<char> towers;
	vector<vector<Vec2D>> towerPositions;

	for (int y = 0; y < map.rowsLen(); y++) {
		for (int x = 0; x < map.colsLen(); x++) {
			char towerChar = map.at(x, y);

			if (towerChar != BLANK_CHAR) {

				// Finding index of tower
				int towerIndex = -1;
				for (int i = 0; i < towers.size(); i++) {
					if (towers[i] == towerChar) { 
						towerIndex = i; 
						break; 
					}
				}

				// Saving position
				if (towerIndex == -1) { 
					towerIndex = towers.size();
					towers.push_back(towerChar);
					towerPositions.push_back(vector<Vec2D>());
				}

				towerPositions[towerIndex].push_back(Vec2D(x, y));
			}
		}
	}

	int count = 0;

	for (vector<Vec2D>& towerArray : towerPositions) {
		for (Vec2D& tower1 : towerArray) {
			for (Vec2D& tower2 : towerArray) {
				if (tower1 != tower2) {
					Vec2D delta = tower2 - tower1;
					int i = 0;
					while (isInMap(map, tower1 + (delta * i))) {
						map.change(tower1 + (delta * i), '#');
						i++;
					}
				}
			}
		}
	}

	for (int y = 0; y < map.rowsLen(); y++) {
		for (int x = 0; x < map.colsLen(); x++) {
			if (map.at(x, y) == '#') {
				count++;
			}
		}
	}

	cout << count << endl;

	return 0;
}