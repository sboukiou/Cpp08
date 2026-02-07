#include <iostream>
#include <vector>
#include "./easyfind.hpp"

void testSimpleVector(void) {
	std::vector<int> Array;
	for (int i = 0; i < 5; i += 1)
		Array.push_back(i);
	int result = easyfind(Array, 3);
	std::cout << "The result of search for number 3 is : " << result << std::endl;
}


int main(void) {
	// Implementing a basic Vector test
	testSimpleVector();
	return (0);
}
