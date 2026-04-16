#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int smallestSide(int l, int w, int h);

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	int total = 0;

	while (std::getline(inFile, line)) {
		size_t x;

		x = line.find('x');
		std::string sub1 = line.substr(0, x);
		line = line.substr(x + 1, line.length());

		x = line.find('x');
		std::string sub2 = line.substr(0, x);
		line = line.substr(x + 1, line.length());

		int l = std::stoi(sub1);
		int w = std::stoi(sub2);
		int h = std::stoi(line);

		int surfaceArea = 2 * ((l * w) + (w * h) + (l * h));
		int padding = smallestSide(l, w, h);

		total += (surfaceArea + padding);
	}
	inFile.close();

	std::cout << "total: " << total << "\n";
	return 0;
}

int smallestSide(int l, int w, int h) {
	int a1 = l * w;
	int a2 = w * h;
	int a3 = l * h;

	if (a1 <= a2 && a1 <= a3) {
		return a1;
	}
	else if (a2 <= a1 && a2 <= a3) {
		return a2;
	}
	else {
		return a3;
	}
}
