#include <iostream>
#include "./Span.hpp"

#define LARGE_SIZE 100000

int main()
{
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;


	Span n = Span(3);
	n.addNumber(2);
	n.addNumber(2);
	n.addNumber(2);
	std::cout << n.shortestSpan() << std::endl;
	std::cout << n.longestSpan() << std::endl;

	n = sp;
	std::cout << n.shortestSpan() << std::endl;
	std::cout << n.longestSpan() << std::endl;

    Span big = Span(LARGE_SIZE);
    for (int i = 0; i < LARGE_SIZE; i += 1)
		big.addNumber(i);
	std::cout << big.shortestSpan() << std::endl;
	std::cout << big.longestSpan() << std::endl;

	return (0);
}
