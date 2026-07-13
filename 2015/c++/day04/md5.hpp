// available standalone in my gists at https://gist.github.com/Hemanth3303/c104014b55e1ff5ab02e6194a91f942f

/*
* Header only implementation of MD5 hashing algorithm (https://www.ietf.org/rfc/rfc1321.txt)
* Passed on the following test suite provided in the rfc with g++ 13.3.0 on ubuntu 24 using --std=c++20
* MD5 test suite:
* MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
* MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
* MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
* MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
* MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
* MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = d174ab98d277d9f5a5611c2c9f419d9f
* MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = 57edf4a22be3c955ac49da2e2107b67a
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>
#include <cstdint>

class MD5 {
public:
	static std::string Compute(const std::string& input) {
		std::vector<uint8_t> inputBuffer(input.begin(), input.end());
		std::vector<uint8_t> padded = Pad(inputBuffer);

		MD5::MD5State state;
		state.A = INITIAL_A;
		state.B = INITIAL_B;
		state.C = INITIAL_C;
		state.D = INITIAL_D;

		for (size_t i = 0; i < padded.size(); i += 64) {
			Transform(state, &padded[i]);
		}

		std::array<uint8_t, 16> digest;
		std::array<uint32_t, 4> values = {
			state.A, state.B, state.C, state.D
		};

		for (int i = 0; i < 4; i++) {
			digest[i * 4 + 0] = values[i] & 0xff;
			digest[i * 4 + 1] = (values[i] >> 8) & 0xff;
			digest[i * 4 + 2] = (values[i] >> 16) & 0xff;
			digest[i * 4 + 3] = (values[i] >> 24) & 0xff;
		}

		std::ostringstream oss;
		oss << std::hex << std::setfill('0');
		for (const uint8_t byte : digest) {
			oss << std::setw(2) << static_cast<uint32_t>(byte);
		}

		return oss.str();
	}
private:
	inline static constexpr std::array<uint32_t, 64> K = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	inline static constexpr std::array<uint32_t, 16> SHIFT_AMOUNTS = {
		7, 12, 17, 22,
		5,  9, 14, 20,
		4, 11, 16, 23,
		6, 10, 15, 21
	};

	inline static constexpr uint32_t BLOCK_SIZE_BITS = 512;
	inline static constexpr uint32_t LEN_INFO_SIZE_BITS = 64;
	inline static constexpr uint32_t MAX_MSG_SIZE_BLOCK_BITS = (512 - LEN_INFO_SIZE_BITS);
	inline static constexpr uint32_t BLOCK_SIZE_BYTES = BLOCK_SIZE_BITS / 8;
	inline static constexpr uint32_t MAX_MSG_SIZE_BLOCK_BYTES = MAX_MSG_SIZE_BLOCK_BITS / 8;

	inline static constexpr uint32_t INITIAL_A = 0x67452301;
	inline static constexpr uint32_t INITIAL_B = 0xefcdab89;
	inline static constexpr uint32_t INITIAL_C = 0x98badcfe;
	inline static constexpr uint32_t INITIAL_D = 0x10325476;
private:
	struct MD5State {
	public:
		uint32_t A;
		uint32_t B;
		uint32_t C;
		uint32_t D;
	};
private:
	// left rotational shift
	static uint32_t LeftRotate(uint32_t x, uint32_t n) {
		return ((x << n) | (x >> (32 - n)));
	}

	static std::vector<uint8_t> Pad(const std::vector<uint8_t>& input) {
		std::vector<uint8_t> padded = input;

		padded.emplace_back(0x80); // 0x80 = 0b10000000 = 128

		while ((padded.size() % BLOCK_SIZE_BYTES) != MAX_MSG_SIZE_BLOCK_BYTES) {
			padded.emplace_back(0x00); // 0x00 = 0b00000000 = 0 (duh)
		}

		uint64_t bitLength = static_cast<uint64_t>(input.size()) * 8;
		for (uint32_t i = 0; i < 8; i++) {
			padded.emplace_back((bitLength >> (8 * i)) & 0xff);
		}

		return padded;
	}

	static void Transform(MD5::MD5State& state, const uint8_t block[64]) {
		uint32_t a = state.A;
		uint32_t b = state.B;
		uint32_t c = state.C;
		uint32_t d = state.D;

		uint32_t M[16];
		for (uint32_t i = 0; i < 16; i++) {
			M[i] = block[i * 4] | (block[i * 4 + 1] << 8) | (block[i * 4 + 2] << 16) | (block[i * 4 + 3] << 24);
		}

		for (uint32_t i = 0; i < 64; i++) {
			uint32_t Fval, g;
			// 4 rounds

			if (i < 16) {
				Fval = F(b, c, d);
				g = i;
			}
			else if (i < 32) {
				Fval = G(b, c, d);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48) {
				Fval = H(b, c, d);
				g = (3 * i + 5) % 16;
			}
			else {
				Fval = I(b, c, d);
				g = (7 * i) % 16;
			}

			uint32_t temp = d;
			d = c;
			c = b;
			uint32_t shiftAmount = SHIFT_AMOUNTS[(i / 16) * 4 + (i % 4)];
			b = b + LeftRotate(a + Fval + K[i] + M[g], shiftAmount);
			a = temp;
		}

		state.A += a;
		state.B += b;
		state.C += c;
		state.D += d;
	}

	static uint32_t F(uint32_t X, uint32_t Y, uint32_t Z) {
		return ((X & Y) | (~X & Z));
	}

	static uint32_t G(uint32_t X, uint32_t Y, uint32_t Z) {
		return ((X & Z) | (Y & ~Z));
	}

	static uint32_t H(uint32_t X, uint32_t Y, uint32_t Z) {
		return (X ^ Y ^ Z);
	}

	static uint32_t I(uint32_t X, uint32_t Y, uint32_t Z) {
		return ((Y ^ (X | ~Z)));
	}
};
