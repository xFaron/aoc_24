#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

template<class T>
inline void debug(T msg) {
	std::cout << msg << std::endl;
}

template<class T>
std::ostream& operator<< (std::ostream& ostream, std::vector<T> array) {
	ostream << "[ ";
	for (int i = 0; i < array.size(); i++) {
		ostream << array[i] << ", ";
	}
	ostream << "]";

	return ostream;
}

struct Rule {
	int before, after;
};

std::ostream& operator<< (std::ostream& ostream, Rule rule) {
	ostream << "Rule( b: " << rule.before << ", a: " << rule.after << " )";

	return ostream;
}


int main() {

	std::string filename = "input2.txt"; // CHANGE INPUT FILE HERE
	std::ifstream inFile(filename);

	if (!inFile) {
		std::cerr << "Unable to open file " << filename << std::endl;
		return 1;
	}

	debug("Opened file " + filename);

	std::vector<Rule> rules;
	std::vector<std::vector<int>> pageSets;
	std::vector<bool> isValid;

	std::string line;
	bool gotRules = false;
	while(std::getline(inFile, line)) {
		if (line == "") {
			gotRules = true;
			continue;
		}
		
		std::istringstream lineStream(line);
		std::string tempLine;

		if (gotRules) {
			std::vector<int> pages;

			while (std::getline(lineStream, tempLine, ',')) {
				pages.push_back(std::stoi(tempLine));
			}

			isValid.push_back(true);
			pageSets.push_back(pages);
		} else {
			int before, after;
			char seperator;

			lineStream >> before >> seperator >> after;
			rules.push_back({before, after});
		}
	}

	int validMiddlePageSum = 0;
	int invalidMiddlePageSum = 0;
	int invalidCases = 0;

	bool firstIter = true;

	do {
		invalidCases = 0;
		for (int i = 0; i < pageSets.size(); i++) {
			std::vector<int>& pages = pageSets[i];
			std::cout << "Checking: " << pages << std::endl;

			if (isValid[i] && !firstIter) continue;
			int caseChange = 0;

			for (const auto& rule : rules) {
				int indexAfter;

				bool foundAfter = false;
				for (int k = 0; k < pages.size(); k++)  {
					int pageNum = pages[k];

					if (foundAfter && pageNum == rule.before) {
						isValid[i] = false;
						caseChange++;
						std::cout << "Before swap: " << pages[indexAfter] << " " << pages[k] << std::endl;
						pages[indexAfter] = pages[indexAfter] + pages[k] - (pages[k] = pages[indexAfter]);
						std::cout << "After swap: " << pages[indexAfter] << " " << pages[k] << std::endl << std::endl;

						break;
					} else if (!foundAfter && pageNum == rule.after) {
						foundAfter = true;
						indexAfter = k;
					}
				}
			}

			invalidCases += caseChange;
		}

		firstIter = false;
	} while (invalidCases);

	debug("Checked page sets");
	for (int i = 0; i < pageSets.size(); i++) {
		if (isValid[i]) {
			validMiddlePageSum += pageSets[i][pageSets[i].size() / 2];
		} else {
			auto array = pageSets[i];

			std::cout << array << std::endl;
			invalidMiddlePageSum += array[array.size() / 2];
		}
	}

	std::cout << "Sum of middle pages of valid page sets: " << validMiddlePageSum << std::endl;
	std::cout << "Sum of middle pages of invalid page sets: " << invalidMiddlePageSum << std::endl;
	

	return 0;
}