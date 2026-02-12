#include <iostream>
#include "./MutanStack.hpp"


int main(void) {
	std::cout << "Test!" << std::endl;
	MutanStack<int> m;
	m.push(12);
	m.push(33);
	std::cout << m.top() << std::endl;
	std::cout << m.size() << std::endl;
	return (0);
}
