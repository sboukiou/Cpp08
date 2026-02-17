#include "./Span.hpp"
#include <climits>
#include <stdexcept>
#include <algorithm>

Span::Span(void) {
	N = 0;
	values.clear();
}

Span::Span(int param) {
	if (param <= 0)
		throw(std::out_of_range("Given size is negative or Null!"));
	N = param;
	values.reserve(N);
}

Span::Span(const Span &other) {
	N = other.N;
	values = other.values;
	values.reserve(N);
}

Span::~Span(void) {}

Span	&Span::operator=(const Span &other) {
	N = other.N;
	values = other.values;
	return (*this);
}

void Span::addNumber(int param) {
	if (static_cast<unsigned int>(values.size()) < N) {
		values.push_back(param);
	}
	else
		throw(std::out_of_range("Span already filled!"));
}

int Span::shortestSpan(void) {
	int result = INT_MAX;
	if (values.size() < 2)
		throw(std::runtime_error("Span is too small!"));

	std::vector<int> temp(values);
	std::sort(temp.begin(), temp.end());
	for (unsigned int i = 0; i < temp.size() - 1; i += 1) {
		if (temp[i + 1] - temp[i] < result)
			result = temp[i + 1] - temp[i];
	}
	return (result);
}

int Span::longestSpan(void) {
	if (values.size() < 2)
		throw(std::runtime_error("Span is too small!"));
	std::vector<int> temp(values);
	std::sort(temp.begin(), temp.end());
	int min = temp[0];
	int max = temp[temp.size() - 1];
	return (max - min);
}
