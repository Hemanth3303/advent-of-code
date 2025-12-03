#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

struct Vec2 {
public:
	Vec2(int px, int py) : x(px), y(py) {}
	bool operator==(const Vec2& other) const {
		return ((x == other.x) && (y == other.y));
	}
public:
	int x, y;
};

namespace std {
	template <>
	struct hash<Vec2> {
		size_t operator()(const Vec2& v) const {
			return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
		}
	};
}

int main() {
	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::stringstream ss;
	ss << inFile.rdbuf();
	std::string instructions = ss.str();

	std::unordered_set<Vec2> gridPoistions;

	Vec2 santaPos{ 0, 0 };
	Vec2 robotPos{ 0, 0 };
	gridPoistions.insert(santaPos);
	gridPoistions.insert(robotPos);

	bool robotTurn = false;
	auto handleInsert = [&](const Vec2& dPos) {
		if (robotTurn) {
			robotPos.x += dPos.x;
			robotPos.y += dPos.y;
			gridPoistions.insert(robotPos);
		}
		else {
			santaPos.x += dPos.x;
			santaPos.y += dPos.y;
			gridPoistions.insert(santaPos);
		}
		robotTurn = !robotTurn;
	};

	for (const char c : instructions) {
		switch (c)
		{
		case '>':
			handleInsert({ 1, 0 });
			break;
		case '<':
			handleInsert({ -1, 0 });
			break;
		case '^':
			handleInsert({ 0, 1 });
			break;
		case 'v':
			handleInsert({ 0, -1 });
			break;
		default:
			break;
		}
	}

	std::cout << "Number of houses: " << gridPoistions.size() << "\n";

	return 0;
}