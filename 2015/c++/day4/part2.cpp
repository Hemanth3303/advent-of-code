#include "md5.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::stringstream ss;
	ss << inFile.rdbuf();

	std::string input = ss.str();

	std::cout << "Computing...\n";
	uint32_t counter = 1;
	while (true) {
		std::string temp = input;
		temp.append(std::to_string(counter));
		std::string hash = MD5::Compute(temp);
		if (hash.substr(0, 6) == "000000") {
			std::cout << "\nN: " << counter << "\n";
			break;
		}
		counter++;
	}

	return 0;
}