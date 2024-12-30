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
		outStream << "( " << position.x << ", " << position.y << ")"; 
		return outStream;
	}

	friend bool operator== (const Position& pos1, const Position& pos2) {
		if (pos1.x == pos2.x && pos1.y == pos2.y) {
			return true;
		}
		return false;
	}

	friend Position operator+ (Position pos1, const Position pos2) {
		pos1.x += pos2.x;
		pos1.y += pos2.y;

		return pos1;
	}

	friend Position operator- (Position pos1, const Position pos2) {
		pos1.x -= pos2.x;
		pos1.y -= pos2.y;

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

	Map(const Map& map) {
		for (int y = 0; y < map.rowsLen(); y++) {
			vector<char> row;
			for (int x = 0; x < map.colsLen(); x++) {
				row.push_back(map.at(x, y));
			}
			matrix.push_back(row);
		}
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

void updateMap(Position& currPos, Map& map, bool fast = false) {
	char guard = map.at(currPos);
	char ahead = map.at(updatePosition(currPos, guard));

	if (ahead == '#') {
		guard = rotateGuard(guard);
		map.change(currPos, guard);
	} else {
		map.change(currPos, 'X');

		if (fast) {
			Position changeVec = updatePosition(currPos, guard) - currPos;
			Position tempPos(currPos);
			while (true) {
				tempPos = tempPos + changeVec;

				if (tempPos.x >= map.colsLen() || tempPos.x < 0 || tempPos.y >= map.rowsLen() || tempPos.y < 0) {
					currPos = tempPos - changeVec;
					break;
				}

				if (map.at(tempPos) == '#') {
					currPos = tempPos - changeVec;
					break;
				}

				map.change(tempPos, 'X');
			}
		} else {
			currPos = updatePosition(currPos, guard);
		}

		map.change(currPos, guard);

	}
}

int main() {

	const string filename = "input2.txt";

	vector<vector<char>> matrix;
	getInput(filename, matrix);

	Map map(matrix);
	Position currPos = getPosition(map);

	int count = 0;
	while (!guardMovesOut(currPos, map)) {
		cout << "Updating" << endl;
		updateMap(currPos, map); // Here, currPos is automatically updated;
		
		bool block_availible = false;
		
		Position changeVec = updatePosition(currPos, rotateGuard(map.at(currPos))) - currPos;
		Position tempPos(currPos);
		while (tempPos.isValid()) {
			tempPos = tempPos + changeVec;

			if (tempPos.x >= map.colsLen() || tempPos.x < 0 || tempPos.y >= map.rowsLen() || tempPos.y < 0) {
				tempPos = Position();
				continue;
			}

			if (map.at(tempPos) == '#') {
				block_availible = true;
				break;
			}
		}

		if (block_availible && !guardMovesOut(currPos, map)) {
			cout << "Block availible!" << endl;

			Map* tempMap = new Map(map);
			tempMap->change(updatePosition(currPos, map.at(currPos)), '#');

			Position* tempPos = new Position(currPos); 

			vector<Position> possibleTurns;
			vector<char> possibleGuard;
			possibleTurns.push_back(currPos);
			possibleGuard.push_back(map.at(currPos));

			bool loopable = false;
			while(!guardMovesOut(*tempPos, *tempMap) && !loopable) {
				updateMap(*tempPos, *tempMap, true);
				cout << *tempMap << endl;
				cout << *tempPos << " " << (*tempPos == currPos) << endl;

				for (int i = 0; i < possibleTurns.size(); i++) {
					Position& turnPos = possibleTurns[i];
					char guardType = possibleGuard[i];

					if (turnPos == *tempPos && guardType == tempMap->at(*tempPos)) {
						cout << "Loopable!" << endl;
						loopable = true;
						count++;
						break;
					}
				}

				possibleTurns.push_back(Position(*tempPos));
				possibleGuard.push_back(tempMap->at(*tempPos));
			} 

			cout << "LoopCheck over" << endl;
			delete tempMap;
			delete tempPos;
		}

	}

	

	cout << "Final Ans: " << count;

	return 0;
}