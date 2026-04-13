#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

int32_t countChars(const std::string& line);
int32_t countMemory(const std::string& line);

int main() {
	int32_t charCount = 0;
	int32_t memoryCount = 0;

	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		charCount += countChars(line);
		memoryCount += countMemory(line);
	}

	inFile.close();

	std::cout << "number of characters: " << charCount << "\n";
	std::cout << "memory needed: " << memoryCount << "\n";

	std::cout << "chars - memory: " << (charCount - memoryCount) << "\n";

	return 0;
}

int32_t countChars(const std::string& line) {
	int32_t count = 0;
	for(const char c: line) {
		count++;
	}

	return count;
}

int32_t countMemory(const std::string& line) {
	size_t index = 1;
	int32_t count = 0;

	while(index < line.size() - 1) {
		if(line[index] == '\\') {
			if(line[index + 1] == 'x') {
				index += 4;
			}
			else {
				index += 2;
			}
		}
		else {
			index++;
		}

		count++;
	}

	return count;
}
