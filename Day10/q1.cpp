#include <iostream>
#include "/home/xfaron/Desktop/Code/Other/AdventOfCode-2024/lib/lib.cpp"

using namespace std;

const string filename = "input2.txt";
const int maxHeightJump = 1;
const int TRAILHEAD = '0';
const int MAXHEIGHT = '9';
const Vec2D directions[] = {Vec2D(0, 1), Vec2D(1, 0), Vec2D(0, -1), Vec2D(-1, 0)};

int traverse(Map& map, Vec2D pos) {
	// char temp = map.at(pos);
	// map.change(pos, '#');
	// cout << map << endl;
	// map.change(pos, temp);
	

	if (map.at(pos) == MAXHEIGHT) {
		map.change(pos, 'X');
		return 1;
	}

	int count = 0;
	for (auto& direction : directions) {
		if (map.isVecInMap(pos + direction) && map.at(pos + direction) - map.at(pos) == maxHeightJump) {
			count += traverse(map, pos + direction);
		}
	}

	return count;
}

int noOfHikingPaths(Map& map) {
	int count = 0;

	for (int y = 0; y < map.rowsLen(); y++) {
		for (int x = 0; x < map.colsLen(); x++) {
			if (map.at(x, y) == TRAILHEAD) {
				Map *tempMap = new Map (map);
				count += traverse(*tempMap, Vec2D(x, y));
				delete tempMap;
			}
		}
	}

	return count;
}

int main() {

	vector<vector<char>> matrix;
	getInput(filename, matrix);

	Map map(matrix);
	cout << noOfHikingPaths(map) << endl;

	return 0;
}