#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdint>
#include <unordered_map>

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	uint32_t niceCount = 0;

	while (std::getline(inFile, line)) {
		bool naughty = false;

		// rule 2 check
		bool hasMirror = false;
		for (uint32_t i = 0; i < line.size() - 1; i++) {
			if (line[i] == line[i + 2]) {
				hasMirror = true;
				break;
			}
		}
		if (!hasMirror) {
			naughty = true;
		}

		// rule 1 check
		std::unordered_map<std::string, uint32_t> positions;
		uint32_t windowSize = 2;
		bool hasRepeatNoOverlap = false;
		for (uint32_t i = 0; i < line.size() - 1; i++) {
			std::string substr = line.substr(i, windowSize);
			if (positions.contains(substr)) {
				if (i >= positions.at(substr) + 2) {
					hasRepeatNoOverlap = true;
					break;
				}
			}
			else {
				positions[substr] = i;
			}
		}

		if (!hasRepeatNoOverlap) {
			naughty = true;
		}

		if (!naughty) {
			niceCount++;
		}
	}
	inFile.close();

	std::cout << "Nice string: " << niceCount << "\n";

	return 0;
}