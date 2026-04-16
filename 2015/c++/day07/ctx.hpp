#pragma once

#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <sstream>

enum class Opcodes {
	None = -1,
	Assign = 0,
	Not = 1,
	And = 2,
	Or = 3,
	LShift = 4,
	RShift = 5,
};

struct Operand {
public:
	bool isInt = false;
	uint16_t value = 0;
	std::string wire = "";
};

struct Instruction {
public:
	Operand op1;
	Operand op2;
	Opcodes opcode = Opcodes::None;
};

struct Context {
public:
	std::unordered_map<std::string, Instruction> instructions;
	std::unordered_map<std::string, uint16_t> cache;
};

std::ostream& operator<<(std::ostream& os, const Operand& operand) {
    if(operand.isInt) {
        os << "Operand(uint16_t, " << operand.value << ")";
    }
    else {
        os << "Operand(wire, " << operand.wire << ")";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Instruction& instr) {
    std::string opcode = "";
    switch (instr.opcode) {
        case Opcodes::None:
            opcode = "undefined opcode error";
            break;
        case Opcodes::Assign:
            opcode = "Assignment";
            break;
        case Opcodes::Not:
            opcode = "NOT";
            break;
        case Opcodes::And:
            opcode = "AND";
            break;
        case Opcodes::Or:
            opcode = "OR";
            break;
        case Opcodes::LShift:
            opcode = "LSHIFT";
            break;
        case Opcodes::RShift:
            opcode = "RSHIFT";
            break;
    }

    os << "Instruction [:\n";
    os << "OPCODE: " << opcode;
    os << ", OP1: " << instr.op1;
    os << ", OP2: " << instr.op2;
    os << "\n]";

    return os;
}