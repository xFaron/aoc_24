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

	bool isVecInMap(const int x, const int y) {
		if (x < 0 || x >= colsLen() || y < 0 || y >= rowsLen()) {
			return false;
		}

		return true;
	}

	bool isVecInMap(const Vec2D& vec) {
		if (vec.x < 0 || vec.x >= colsLen() || vec.y < 0 || vec.y >= rowsLen()) {
			return false;
		}

		return true;
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
