#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

int32_t countChars(const std::string& line);
std::string encode(const std::string& line);

int main() {
	int32_t orignalCharCount = 0;
	int32_t transformedCharCount = 0;

	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		orignalCharCount += countChars(line);
		std::string transformedLine = encode(line);
		transformedCharCount += countChars(transformedLine);
	}

	inFile.close();

	std::cout << "orignal number of characters: " << orignalCharCount << "\n";
	std::cout << "new number of characters: " << transformedCharCount << "\n";

	std::cout << "new - original: " << (transformedCharCount - orignalCharCount) << "\n";

	return 0;
}

int32_t countChars(const std::string& line) {
	int32_t count = 0;
	for(const char c: line) {
		count++;
	}

	return count;
}

std::string encode(const std::string& line) {
	std::string transformedLine = "";
	size_t index = 0;

	transformedLine += '\"';

	while(index < line.size()) {
		if(line[index] == '\"' || line[index] == '\\') {
			transformedLine += '\\';
		}

		transformedLine += line[index];
		index++;

	}

	transformedLine += '\"';

	std::cout << "original: " << line << " | transformed: " << transformedLine << "\n";
	return transformedLine;
}
