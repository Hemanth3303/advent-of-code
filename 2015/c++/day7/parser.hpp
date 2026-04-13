#pragma once

#include "ctx.hpp"

#include <cctype>
#include <vector>
#include <sstream>
#include <string>

bool isDigit(const std::string& input) {
	for (const char c : input) {
		if(!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

std::vector<std::string> tokenize(const std::string& line) {
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	std::string token;

	while(iss >> token) {
		tokens.push_back(token);
	}

	return tokens;
}

Operand parseOperand(const std::string& token) {
	Operand op;
	if (isDigit(token)) {
		op.isInt = true;
		op.value = static_cast<uint16_t>(std::stoul(token));
		op.wire = "";
	} else {
		op.isInt = false;
		op.wire = token;
		op.value = 0;
	}
	return op;
}

void parseLine(Context& ctx, const std::string& line) {
	std::vector<std::string> tokens = tokenize(line);
	Instruction instr;

	if(tokens.size() == 5) {
		instr.op1 = parseOperand(tokens[0]);
		instr.op2 = parseOperand(tokens[2]);

		if(tokens[1] == "AND") {
			instr.opcode = Opcodes::And;
		}
		else if(tokens[1] == "OR") {
			instr.opcode = Opcodes::Or;
		}
		else if(tokens[1] == "LSHIFT") {
			instr.opcode = Opcodes::LShift;
		}
		else if(tokens[1] == "RSHIFT") {
			instr.opcode = Opcodes::RShift;
		}
		else {
			std::cerr << "Invalid Instruction\n";
			return;
		}

		ctx.instructions[tokens[4]] = instr;
	}
	else if (tokens.size() == 4) {
		if(tokens[0] != "NOT") {
			std::cerr << "Invalid Instruction\n";
			return;
		}
		instr.opcode=Opcodes::Not;
		instr.op1=parseOperand(tokens[1]);

		ctx.instructions[tokens[3]] = instr;
	}
	else if (tokens.size() == 3) {
		instr.op1=parseOperand(tokens[0]);
		instr.opcode = Opcodes::Assign;
		ctx.instructions[tokens[2]] = instr;
	}
	else {
		std::cerr << "Invalid Instruction\n";
		return;
	}
}
