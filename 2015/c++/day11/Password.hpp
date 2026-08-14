#pragma once

#include <array>
#include <string>
#include <string_view>
#include <iostream>
#include <cstddef>
#include <cstdlib>

inline static constexpr size_t PASSWORD_LENGTH = 8;

class Password {
public:
	Password(std::string_view passwordString) {
		if (passwordString.size() != PASSWORD_LENGTH) {
			std::cerr << "[ERROR]: only passwords of length " << PASSWORD_LENGTH << " are accepted\n";
			std::abort();
		}

		for (size_t i = 0; i < letters.size(); i++) {
			letters[i] = passwordString[i];
		}
	}

	~Password() = default;

	friend std::ostream& operator<<(std::ostream& os, const Password& password);

	const char& operator[](size_t index) const {
		if (index >= letters.size()) {
			std::cerr << "[ERROR]: Index out of bounds\n";
			std::abort();
		}

		return letters[index];
	}

	inline constexpr size_t size() const { return letters.size(); }

	// prefix operator
	Password& operator++() {
		for (ptrdiff_t i = static_cast<ptrdiff_t>(letters.size()) - 1; i >= 0; i--) {
			if (letters[i] != 'z') {
				++letters[i];
				return *this;
			}

			letters[i] = 'a';
		}

		return *this;
	}

	// for future reference, postfix is like this
	// NOTE: param must be int, apparantly compiler supplies arg, something about dummy params, idk
	// Password operator++(int) {
	// 	// store old
	// 	// increment value
	// 	// return old
	// }

private:
	std::array<char, PASSWORD_LENGTH> letters{};
};

std::ostream& operator<<(std::ostream& os, const Password& password) {
	for (size_t i = 0; i < password.letters.size(); i++) {
		os << password.letters[i];
	};

	return os;
}
