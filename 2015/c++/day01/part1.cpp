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

	std::string contents;
	std::string line;

	while (std::getline(inFile, line)) {
		contents += line;
		contents += '\n';
	}
	inFile.close();

	int floor = 0;
	for (const char c : contents) {
		if (c == '(') {
			floor++;
		}
		else if (c == ')') {
			floor--;
		}
	}
	std::cout << "Floor: " << floor << "\n"; // should be 280
	return 0;
}
