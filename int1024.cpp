#include "int1024.h"


#include <iostream>
std::string int1024::to_b64_string() {
	static const char base64[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'+', '/'
	};
	std::cout << base64[63] << std::endl;
	return "unimplemented";
}

std::string int1024::to_hex_string() {
	static const char base16[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	};

	for (int i = size(); i > 0; i-=4) {
		std::cout
			<< (*this)[i-1]
			<< (*this)[i-2]
			<< (*this)[i-3]
			<< (*this)[i-4]
			<< " ";
	}
	std::cout << std::endl;

	for (int i = size(); i > 0; i-=4) {
		if (i%8 == 0)
			std::cout << ' ';
		int hex = (*this)[i-1] * 8
			+ (*this)[i-2] * 4
			+ (*this)[i-3] * 2
			+ (*this)[i-4] * 1;
		std::cout << base16[hex];
	}
	std::cout << std::endl;

	return std::to_string(size());
}
std::string int1024::to_int_string() {
	return std::to_string(size());
}


int1024 int1024::operator+(const int1024 & other) const {
	int1024 result = 0;
	int carry_in = 0;
	int carry_out = 0;

	carry_in  = (*this)[0] & other[0];
	result[0] = (*this)[0] ^ other[0];

	for (size_t i = 1; i < size(); ++i) {
		int xor1 = (*this)[i] ^ other[i];
		int and1 = (*this)[i] & other[i];

		carry_out = and1 | (xor1 & carry_in);

		result[i] = xor1 ^ carry_in;
		carry_in = carry_out;
		//std::cout << "i=" << i << " a=" << (*this)[i] << " b=" << other[i] << " Cout=" << carry_in << std::endl;
	}

	return result;
}

int1024 int1024::operator-(const int1024 & other) const {
	int1024 other2 = other;
	other2.flip();
	return (*this) + other2 + 1;
}

int1024 int1024::operator*(const int1024 & other) const {
	(void) other;
	return 0;
}

int1024 int1024::operator/(const int1024 & other) const {
	(void) other;
	return 0;
}

int1024 int1024::operator%(const int1024 & other) const {
	(void) other;
	return 0;
}