#include <iostream>
#include <string>
#include "int1024.h"

int main() {
	int1024 i1(11111111111111);
	int1024 i2(22222222222222);
	int1024 i3 = i1 + i2;
	int1024 i4 = i3 - i2;

	std::cout << i1.to_ullong() << std::endl;
	std::cout << i2.to_ullong() << std::endl;
	std::cout << i3.to_ullong() << std::endl;
	//std::cout << i3.to_string() << std::endl;
	std::cout << i4.to_string() << std::endl;
	std::cout << i4.to_ullong() << std::endl;

	//std::cout << i1.to_string() << std::endl;
	//std::cout << i1.to_b64_string() << std::endl;
	//std::cout << i1.to_hex_string() << std::endl;
	//std::cout << i1.to_int_string() << std::endl;

}