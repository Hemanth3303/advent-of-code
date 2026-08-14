#include "Password.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

bool isValid(const Password& password);

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "Usage: ./solution.out password\n";
		return EXIT_FAILURE;
	}

	std::string inputPassword(argv[1]);
	if (inputPassword.size() != PASSWORD_LENGTH) {
		std::cerr << "[ERROR]: only passwords of length " << PASSWORD_LENGTH << " are accepted\n";
		return EXIT_FAILURE;
	}

	Password password(inputPassword);
	do {
		++password;
	} while(!isValid(password));

	std::cout << "New password: " << password << '\n';

	return EXIT_SUCCESS;
}

bool isValid(const Password& password) {
	// std::cout << "Attempting password: " << password << '\n';
	bool increasingRuleSatisfied = false;
	size_t uniquePairCount = 0;

	for (size_t i = 0; i < password.size(); i++) {
		if (password[i] == 'i' ||
			password[i] == 'o' ||
			password[i] == 'l') {
			return false;
		}
	}

	for (size_t i = 0; i + 2 < password.size(); i++) {
		if ((password[i] + 1 == password[i + 1]) && (password[i] + 2 == password[i + 2])) {
			increasingRuleSatisfied = true;
			break;
		}
	}

	for (size_t i = 0; i + 1 < password.size(); i++) {
		if (password[i] == password[i + 1]) {
			uniquePairCount++;
			i++;
		}
	}

	return increasingRuleSatisfied && (uniquePairCount >= 2);
}
