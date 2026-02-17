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
}

Span::Span(const Span &other) {
	N = other.N;
	values = other.values;
}

Span::~Span(void) {}

Span	&Span::operator=(const Span &other) {
	if (other.values.empty() || other.N == 0)
		throw(std::runtime_error("Given copy is empty"));
	N = other.N;
	for (unsigned int i = 0; i < other.values.size(); i += 1)
		values.push_back(other.values[i]);
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
	int temp;
	if (values.size() < 2)
		throw(std::runtime_error("Span is too small!"));
	std::sort(values.begin(), values.end());
	for (unsigned int i = 0; i < values.size() - 1; i += 1) {
		if (values[i + 1] - values[i] < result)
			result = values[i + 1] - values[i];
	}
	return (result);
}

int Span::longestSpan(void) {
	if (values.size() < 2)
		throw(std::runtime_error("Span is too small!"));
	std::sort(values.begin(), values.end());
	int max = values[0];
	int min = values[values.size() - 1];
	return (max - min);
}
