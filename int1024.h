#ifndef INT1024_H
#define INT1024_H

#include <bitset>
#include <string>

#define BITSET_SIZE 128

class int1024 : public std::bitset<BITSET_SIZE> {
public:
	int1024() : std::bitset<BITSET_SIZE>() {}
	int1024(const std::string & s) : std::bitset<BITSET_SIZE>(s) {}
	int1024(unsigned long long n) : std::bitset<BITSET_SIZE>(n) {}
	//int1024 operator~() const;
	int1024 operator+(const int1024 & other) const;
	int1024 operator-(const int1024 & other) const;
	int1024 operator*(const int1024 & other) const;
	int1024 operator/(const int1024 & other) const;
	int1024 operator%(const int1024 & other) const;

	std::string to_b64_string();
	std::string to_hex_string();
	std::string to_int_string();
};

#undef BITSET_SIZE
#endif
