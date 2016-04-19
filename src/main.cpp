#include <iostream>
#include <string>
#include "graphics.hpp"
#undef main
int main(){
	Graphics g;
	g.run();
	std::cout << "Hello " << std::endl;
	std::string hello;
	std::cin >> hello;
	return 0;
}