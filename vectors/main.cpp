#include <iostream>
#include <string>
#include "FCIvector.h"
#include "FCIvector.cpp"



int main(){
	FCIvector<int> vect;
	vect.push_back(100); vect.push_back(102); vect.push_back(104);
	std::cout << vect << std::endl;
	vect.pop_back();

	std::cout << vect << std::endl;
	vect.push_back(104), vect.push_back(106);
	vect.insert(vect.begin() + 1, 20);
	std::cout << vect << std::endl;
	vect.clear();
	std::cout << vect << std::endl;
	vect.push_back(10), vect.push_back(12), vect.push_back(14), vect.push_back(16);
	std::cout << vect << std::endl;
	vect.erase(vect.begin() + 2);
	std::cout << vect << std::endl;
	vect.erase(vect.begin() + 1);
	std::cout << vect << std::endl;
	try{
		vect.erase(vect.begin() + 10);
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
	}
	std::cout << vect << std::endl;



	return 0;
}
