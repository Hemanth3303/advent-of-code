#pragma once

#include "ctx.hpp"

#include <iostream>
#include <cstdint>

uint16_t resolve(Context& ctx, const std::string& wire);

uint16_t evalOperand(Context& ctx, const Operand& op) {
	if(op.isInt) {
		return op.value;
	}
	return resolve(ctx, op.wire);
}

uint16_t resolve(Context& ctx, const std::string& wire) {
	if(ctx.cache.find(wire) != ctx.cache.end()) {
		return ctx.cache[wire];
	}
	uint16_t result = 0;
	const Instruction& instr = ctx.instructions.at(wire);
	switch(instr.opcode) {
 		case Opcodes::None:
			std::cerr << "Error: Instruction Missing, something went wrong\n";
            break;
        case Opcodes::Assign:
			result = evalOperand(ctx, instr.op1);
            break;
        case Opcodes::Not:
			result = ~evalOperand(ctx, instr.op1);
            break;
        case Opcodes::And:
			result = evalOperand(ctx, instr.op1) & evalOperand(ctx, instr.op2);
            break;
        case Opcodes::Or:
			result = evalOperand(ctx, instr.op1) | evalOperand(ctx, instr.op2);
            break;
        case Opcodes::LShift:
			result = evalOperand(ctx, instr.op1) << evalOperand(ctx, instr.op2);
            break;
        case Opcodes::RShift:
			result = evalOperand(ctx, instr.op1) >> evalOperand(ctx, instr.op2);
            break;
	}

	result &= 0xFFFF;
	ctx.cache[wire] = result;

	return result;
}
