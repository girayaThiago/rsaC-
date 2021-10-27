#include "int1024.h"

#include <stack>
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
void int1024::to_mpz_string(){
	mpz_t num;
	mpz_init(num);
	mpz_set_str(num,this->to_string().c_str(), 2);
	mpz_out_str(stdout, 10, num);
	std::cout << std::endl;
	mpz_clear(num);
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
	int1024 other2 = other;
	std::stack<int> s;
	while(other2 > 1){
		if (other2[0]){
			s.push(1);
			other2 = other2-1;
		} else {
			s.push(0);
			other2 >>= 1;
		}
	}
	other2 = *this;
	while (!s.empty())
	{
		if (!s.top()){
			other2 <<=1;
		}else {
			other2 = *this + other2;
		}
		s.pop();
	}
	return other2;
}

bool int1024::operator<(const int1024 & other) const{
	return !(*this >= other);
}
bool int1024::operator>(const int1024 & other) const{
	return (!(*this < other) && !(*this == other));
}

bool int1024::operator==(const int1024 & other) const{
	int1024 other2 = (*this-other);
	if (other2.count()){
		return false;
	} else {
		return true;
	}	
}
bool int1024::operator!=(const int1024 & other) const{
	return !((*this) == other);	
}
bool int1024::operator<=(const int1024 & other) const{
	int1024 temp = *this;
	return !(temp > other);
}
bool int1024::operator>=(const int1024 & other) const{
	int sthis = (*this)[size()-1], sother = other[other.size()-1];
	if (sthis > sother) return true;
	else if (sthis < sother) return false;
	else {
		int1024 other2 = (*this-other);
		int ssub = other2[other2.size()-1];
		if (sthis){
			return sthis != ssub;
		} else {
			return sthis == ssub;
		}
	}
}

int1024 int1024::operator/(const int1024 & other) const {
	mpz_t num, num2, num3;
	mpz_inits(num, num2, num3, NULL);
	mpz_set_str(num,this->to_string().c_str(), 2);
	mpz_set_str(num2,other.to_string().c_str(), 2);
	mpz_div(num3, num, num2);
	char c[1025];
	mpz_get_str(c,2,num3);
	int1024 test = std::string(c);
	mpz_clears(num, num2, num3, NULL);
	return test;
}

int1024 int1024::operator%(const int1024 & other) const {
	mpz_t num, num2, num3;
	mpz_inits(num, num2, num3, NULL);
	mpz_set_str(num,this->to_string().c_str(), 2);
	mpz_set_str(num2,other.to_string().c_str(), 2);
	mpz_mod(num3, num, num2);
	char c[1025];
	mpz_get_str(c,2,num3);
	int1024 test = std::string(c);
	mpz_clears(num, num2, num3, NULL);
	return test;
}

int1024& int1024::operator+=(const int1024 & other){
	*this = *this + other;
	return *this;
}
int1024& int1024::operator-=(const int1024 & other){
	*this = *this - other;
	return *this;
}
int1024& int1024::operator*=(const int1024 & other){
	*this = *this * other;
	return *this;
}
int1024& int1024::operator/=(const int1024 & other){
	*this = *this / other;
	return *this;
}
int1024 int1024::operator++(int){
	int1024 copy = *this;
	*this = copy + 1;
	return copy;
}
int1024 int1024::operator--(int){
	int1024 copy = *this;
	*this = copy - 1;
	return copy;
}
bool int1024::odd(){
	return (*this)[0] & 1;
}
bool int1024::even(){
	return !odd();
}

// retorna um numero de 1024 bits aleatório entre min e max
int1024 int1024::random(int1024 min, int1024 max, gmp_randstate_t randstate){
	mpz_t num1, num2, num3;
	mpz_inits(num1, num2, num3, NULL);
	mpz_set_str(num1,min.to_string().c_str(), 2);
	mpz_set_str(num2,max.to_string().c_str(), 2);
	// max = max - min;
	mpz_sub(num2, num2, num1);
	// gera um inteiro sem sinal de 0 ate max-1
	mpz_urandomm(num3, randstate, num2);
	// num3 = num3 + min;
	mpz_add(num3, num1, num3);
	// mpz_out_str(stdout,2,num3);
	char c[1025];
	mpz_get_str(c,2,num3);
	int1024 test = std::string(c);
	mpz_clears(num1, num2, num3, NULL);
	return test;
}

std::vector<uint8_t> int1024::to_vec8(){
	std::vector<uint8_t> v;
	int1024 copy = *this;
	v.clear();
	std::cout << ":D" << std::endl;
	for (int i = 0; i < size()/8; i++){
		int1024 byte = 0xFF;
		byte &= copy;
		copy >>=8;
		v.emplace_back(byte.to_ulong());
	}
	std::reverse(v.begin(), v.end());
	return v;
}