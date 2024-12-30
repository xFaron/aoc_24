#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Position {
public:
	int x;
	int y;

	Position() {
		x = -1;
		y = -1;
	}

	Position (int xCord, int yCord) {
		x = xCord;
		y = yCord;
	}

	bool isValid() {
		if (x == -1 && y == -1) {
			return false;
		}

		return true;
	}

	friend ostream& operator<< (ostream& outStream, const Position& position) {
		outStream << "( ," << position.x << ", " << position.y << ")"; 
		return outStream;
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

	char at(const Position& position) const {
		return matrix[position.y][position.x];
	}

	void change(const int x, const int y, char temp) {
		matrix[y][x] = temp;
	}

	void change(const Position& position, char temp) {
		matrix[position.y][position.x] = temp;
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

Position getPosition(const Map& map) {
	Position position;
	for (int y = 0; y < map.rowsLen(); y++) {
		for (int x = 0; x < map.colsLen(); x++) {
			if (map.at(x,y) == '^' || map.at(x,y) == 'v' || map.at(x,y) == '>' || map.at(x,y) == '<') {
				position.x = x;
				position.y = y;

				return position;
			}
		}
	}

	return position;
}

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

bool guardMovesOut(const Position& currPos, Map& map) {
	const char guard = map.at(currPos);

	if ((currPos.x == 0 && guard == '<') || (currPos.x == map.colsLen() - 1 && guard == '>')
	|| (currPos.y == 0 && guard == '^') || (currPos.y == map.rowsLen() - 1 && guard == 'v')) {
		return true;
	}

	return false;
}

char rotateGuard(char guard) {
	if (guard == '^') return '>';
	if (guard == '>') return 'v';
	if (guard == 'v') return '<';
	if (guard == '<') return '^';
}

Position updatePosition(Position position, char guard) {
	if (guard == '^') position.y -= 1;
	if (guard == '>') position.x += 1;
	if (guard == 'v') position.y += 1;
	if (guard == '<') position.x -= 1;

	return position;
}

void updateMap(Position& currPos, Map& map) {
	char guard = map.at(currPos);
	char ahead = map.at(updatePosition(currPos, guard));

	if (ahead == '#') {
		guard = rotateGuard(guard);
		map.change(currPos, guard);
	} else {
		map.change(currPos, 'X');
		currPos = updatePosition(currPos, guard);
		map.change(currPos, guard);
	}
}

int main() {

	const string filename = "input1.txt";

	vector<vector<char>> matrix;
	getInput(filename, matrix);

	Map map(matrix);
	Position currPos = getPosition(map);

	while (!guardMovesOut(currPos, map)) {
		updateMap(currPos, map); // Here, currPos is automatically updated;
		cout << map << endl << endl;
	}

	int count = 0;
	for (int y = 0; y < map.rowsLen(); y++) {
		for (int x = 0; x < map.colsLen(); x++) {
			if (map.at(x, y) == 'X') count++;
		}
	}

	cout << "Final Ans: " << count + 1;

	return 0;
}