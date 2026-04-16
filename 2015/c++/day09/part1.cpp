#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

int main() {
    std::unordered_map<std::string, std::unordered_map<std::string, int32_t>> distances;
    std::unordered_set<std::string> cities;

	std::string fileName = "input.txt";
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Could not open file " << fileName << "\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
        std::istringstream iss(line);

        std::string city1, city2, dist, temp;

        iss >> city1;
        iss >> temp;
        iss >> city2;
        iss >> temp;
        iss >> dist;

        distances[city1][city2] = std::stoi(dist);
        distances[city2][city1] = std::stoi(dist);
        cities.insert(city1);
        cities.insert(city2);

	}

	inFile.close();

    for(const auto& city : cities) {
        distances[city][city] = 0;
    }

    std::vector<std::string> cityList(cities.begin(), cities.end());
    std::sort(cityList.begin(), cityList.end());

    std::cout << "Distance Table: \n";
    std::cout << std::setw(10) << "";
    for (const auto& c : cityList) {
        std::cout << std::setw(10) << c;
    }
    std::cout << "\n";

    for (const auto& from : cityList) {
        std::cout << std::setw(10) << from;

        for (const auto& to : cityList) {
            std::cout << std::setw(10) << distances[from][to];
        }

        std::cout << "\n";
    }

    int32_t bestCost = std::numeric_limits<int32_t>::max();

    do {
        int cost = 0;
        for(size_t i = 0; i < cityList.size() - 1; i++) {
            cost += distances[cityList[i]][cityList[i + 1]];
        }

        if(cost < bestCost) {
            bestCost = cost;
        }
    }
    while(std::next_permutation(cityList.begin(), cityList.end()));

    std::cout << "best cost: " << bestCost << "\n"; 
	return 0;
}
