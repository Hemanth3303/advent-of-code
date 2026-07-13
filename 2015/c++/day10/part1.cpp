#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	std::getline(inFile, line);

	std::string resultString = line;

	for(size_t i = 0; i < 40; i++ ) {
		int32_t count = 0;
		char current = resultString[0];
		std::string temp = "";
		for(size_t j =0; j < resultString.size(); j++) {
			if(current != resultString[j]) {
				// std::cout << "(" << count << ", " << current << ") \n";
				temp += std::to_string(count) + current;
				count = 1;
				current = resultString[j];
			}
			else {
				count++;
			}
		}

		temp += std::to_string(count) + current;

		resultString = temp;
	}

	std::cout << "size of result string: " << resultString.size() << "\n";

	return 0;
}
