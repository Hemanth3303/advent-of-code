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
	int pos = 0;
	for (int i = 0; i < contents.size(); i++) {
		if (contents[i] == '(') {
			floor++;
		}
		else if (contents[i] == ')') {
			floor--;
		}

		if (floor == -1) {
			pos = i + 1;
			break;
		}
	}
	std::cout << "position " << pos << "\n"; //should be 1797
	return 0;
}
