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

	Vec2 position{ 0, 0 };
	gridPoistions.insert(position);

	for (const char c : instructions) {
		switch (c)
		{
		case '>':
			position.x++;
			gridPoistions.insert(position);
			break;
		case '<':
			position.x--;
			gridPoistions.insert(position);
			break;
		case '^':
			position.y++;
			gridPoistions.insert(position);
			break;
		case 'v':
			position.y--;
			gridPoistions.insert(position);
			break;
		default:
			break;
		}
	}

	std::cout << "Number of houses: " << gridPoistions.size() << "\n";

	return 0;
}