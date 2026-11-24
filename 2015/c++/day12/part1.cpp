#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    std::string fileName = "input.json";
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file " << fileName << "\n";
        return 1;
    }

    std::string line;
    long acc = 0;
    while (std::getline(inFile, line)) {
        std::string temp = "";

        for (char c : line) {
            if (std::isdigit(static_cast<unsigned char>(c)) || (c == '-' && temp.empty())) {
                temp += c;
            }
			else {
                if (temp.empty()) {
                    continue;
                }
                long n = std::stol(temp);
                acc += n;
                temp.clear();
            }
        }
        if (temp.empty()) {
            continue;
        }
        long n = std::stol(temp);
        acc += n;
    }

    std::cout << acc << '\n';
    return 0;
}
