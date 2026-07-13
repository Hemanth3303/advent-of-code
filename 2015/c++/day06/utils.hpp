#pragma once

#include <cstdint>
#include <sstream>

enum class OPCODES {
	UNDEFINED = -1,
	TURN_OFF = 0,
	TURN_ON = 1,
	TOGGLE = 2,
};

struct Command {
public:
	OPCODES opcode = OPCODES::UNDEFINED;
	uint32_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

static const Command parseLine(const std::string& line) {
	std::stringstream ss(line);
	std::string word, temp, first, second;
	Command cmd;

	ss >> word;
	if (word == "turn") {
		ss >> temp;
		if (temp == "on") {
			cmd.opcode = OPCODES::TURN_ON;
		}
		else {
			cmd.opcode = OPCODES::TURN_OFF;
		}
	}
	else {
		cmd.opcode = OPCODES::TOGGLE;
	}

	ss >> first;
	ss >> temp; // the "through"
	ss >> second;

	auto parseComma = [](const std::string& str, uint32_t& x, uint32_t& y) {
		size_t commaPos = str.find(",");
		x = std::stoi(str.substr(0, commaPos));
		y = std::stoi(str.substr(commaPos + 1));
	};

	parseComma(first, cmd.x1, cmd.y1);
	parseComma(second, cmd.x2, cmd.y2);

	return cmd;
}
