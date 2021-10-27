#ifndef INT1024_H
#define INT1024_H

#include <bitset>
#include <string>
#include "include.hpp"
#define BITSET_SIZE 1024

class int1024 : public std::bitset<BITSET_SIZE> {
public:
	int1024() : std::bitset<BITSET_SIZE>() {}
	int1024(const std::string & s) : std::bitset<BITSET_SIZE>(s) {}
	int1024(const std::vector<uint8_t> & s): std::bitset<BITSET_SIZE>() {
		for (int i  = 0; i < s.size(); i++){ 
			//big endian
			int1024 block;
			block = s[i];
			block <<= 8*(i);
			(*this) |= block;
			// //little endian
			// int1024 block;
			// block = s[i];
			// block <<= size()-8*(i+1);
			// (*this) |= block;
		}
		
	}
	int1024(unsigned long long n) : std::bitset<BITSET_SIZE>(n) {}
	//int1024 operator~() const;
	int1024 operator+(const int1024 & other) const;
	int1024 operator-(const int1024 & other) const;
	int1024 operator*(const int1024 & other) const;
	int1024 operator/(const int1024 & other) const;
	int1024 operator%(const int1024 & other) const;
	bool operator<(const int1024 & other) const;
	bool operator>(const int1024 & other) const;
	bool operator==(const int1024 & other) const;
	bool operator!=(const int1024 & other) const;
	bool operator>=(const int1024 & other) const;
	bool operator<=(const int1024 & other) const;
	bool odd();
	bool even();
	int1024& operator+=(const int1024 & other);
	int1024& operator-=(const int1024 & other);
	int1024 operator++(int);
	int1024 operator--(int);
	int1024& operator*=(const int1024 & other);
	int1024& operator/=(const int1024 & other);
	std::string to_b64_string();
	std::string to_hex_string();
	std::string to_int_string();
};

#undef BITSET_SIZE
#endif
