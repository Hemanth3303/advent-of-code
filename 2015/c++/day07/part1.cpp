#include "parser.hpp"
#include "resolver.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
	Context ctx;
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		parseLine(ctx, line);
	}
	inFile.close();

	// for(const auto& [wire, instr]: ctx.instructions) {
	// 	std::cout << "wire: " << wire << "\n";
	// 	std::cout << instr << "\n";
	// }

	uint16_t result = resolve(ctx, "a");
	std::cout << "Value of wire 'a': " << result << "\n";

	return 0;
}
