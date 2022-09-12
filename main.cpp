#include <iostream>
#include <string>
#include "BigNum.h" 

int main()
{
	std::string str = "0000012345678";
	//std::cin >> str;
	
	BigNum a(str);
	
	BigNum b("57442343345434518822");

	BigNum c("53453453326263632533453456456346235325253532532535353");

	std::cout << (a + b * c);

	return 0;
}
