#include "parser.hpp"
#include "resolver.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
	Context ctx1, ctx2;
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		parseLine(ctx1, line);
		parseLine(ctx2, line);
	}
	inFile.close();

	uint16_t a1 = resolve(ctx1, "a");
	std::cout << "Value of wire 'a' in ctx1: " << a1 << "\n";

    Instruction overrideInstr;
    overrideInstr.opcode = Opcodes::Assign;
    overrideInstr.op1.isInt = true;
    overrideInstr.op1.value = a1;

    ctx2.instructions["b"] = overrideInstr;

    uint16_t a2 = resolve(ctx2, "a");
	std::cout << "Value of wire 'a' in ctx2: " << a2 << "\n";

	return 0;
}
