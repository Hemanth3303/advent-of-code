#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int minPerimeter(int l, int w, int h);

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

		int surfaceArea = minPerimeter(l, w, h);
		int padding = l * w * h;

		total += (surfaceArea + padding);
	}
	inFile.close();

	std::cout << "total: " << total << "\n";
	return 0;
}

int minPerimeter(int l, int w, int h) {
	int p1 = 2 * l + 2 * w;
	int p2 = 2 * w + 2 * h;
	int p3 = 2 * l + 2 * h;

	if (p1 <= p2 && p1 <= p3) {
		return p1;
	}
	else if (p2 <= p1 && p2 <= p3) {
		return p2;
	}
	else {
		return p3;
	}
}
