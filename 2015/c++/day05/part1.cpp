#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdint>

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	const std::string vowels = "aeiou";
	std::array<std::string, 4> dissallowed = { "ab", "cd", "pq", "xy" };
	std::string line;

	uint32_t niceCount = 0;

	while (std::getline(inFile, line)) {
		bool naughty = false;

		for (const auto& str : dissallowed) {
			if (line.find(str) != std::string::npos) {
				naughty = true;
				break;
			}
		}

		uint32_t vowelCount = 0;
		for (const char c : line) {
			if (vowels.find(c) != std::string::npos) {
				vowelCount++;
			}
		}
		if (vowelCount < 3) {
			naughty = true;
		}

		uint32_t repeatedCount = 0;
		for (size_t i = 0; i < line.size() - 1; i++) {
			if (line[i] == line[i + 1]) {
				repeatedCount++;
			}
		}
		if (!repeatedCount) {
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