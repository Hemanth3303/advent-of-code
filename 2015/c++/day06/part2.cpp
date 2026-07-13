#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cstdint>
#include <cmath>

template <uint32_t Length, uint32_t Width>
class LEDGrid {
public:
	LEDGrid() {
		for (auto& led : m_Grid) {
			led = 0;
		}
	}
	~LEDGrid() {}

	void turnOn(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
		for (uint32_t y = y1; y <= y2; y++) {
			for (uint32_t x = x1; x <= x2; x++) {
				m_Grid[y * Width + x] += 1;
			}
		}
	}

	void turnOff(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
		for (uint32_t y = y1; y <= y2; y++) {
			for (uint32_t x = x1; x <= x2; x++) {
				m_Grid[y * Width + x] = std::max(0, m_Grid[y * Width + x] - 1);
			}
		}
	}

	void toggle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
		for (uint32_t y = y1; y <= y2; y++) {
			for (uint32_t x = x1; x <= x2; x++) {
				m_Grid[y * Width + x] += 2;
			}
		}
	}

	const uint32_t countOn() const {
		uint32_t acc = 0;
		for (const auto& led : m_Grid) {
			if (led) {
				acc += led;
			}
		}
		return acc;
	}
private:
	std::array<int32_t, Length * Width> m_Grid;
};

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::vector<Command> commandBuffer;
	std::string line;

	while (std::getline(inFile, line)) {
		Command cmd = parseLine(line);
		commandBuffer.push_back(cmd);
	}
	inFile.close();

	LEDGrid<1000, 1000> ledGrid;
	for (const auto& cmd : commandBuffer) {
		switch (cmd.opcode) {
		case OPCODES::TURN_ON:
			ledGrid.turnOn(cmd.x1, cmd.y1, cmd.x2, cmd.y2);
			break;
		case OPCODES::TURN_OFF:
			ledGrid.turnOff(cmd.x1, cmd.y1, cmd.x2, cmd.y2);
			break;
		case OPCODES::TOGGLE:
			ledGrid.toggle(cmd.x1, cmd.y1, cmd.x2, cmd.y2);
			break;
		case OPCODES::UNDEFINED:
		default:
			std::cerr << "undefined opcode\n";
			break;
		}
	}

	std::cout << "Total Brightness = " << ledGrid.countOn() << "\n";

	return 0;
}
