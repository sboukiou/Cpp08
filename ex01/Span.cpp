#include "./Span.hpp"
#include <climits>
#include <stdexcept>

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
	for (unsigned int i = 0; i < N; i += 1)
		for (unsigned int j = 0; j < N - 1; j += 1) {
			if (values[j] > values[j + 1]) {
				temp = values[j];
				values[j] = values[j + 1];
				values[j + 1] = temp;
			}
		}
	for (unsigned int i = 0; i < N - 1; i += 1) {
		if (values[i + 1] - values[i] < result)
			result = values[i + 1] - values[i];
	}
	return (result);
}

int Span::longestSpan(void) {
	int max = INT_MIN;
	int min = INT_MAX;
	int result;

	if (N < 2)
		throw(std::runtime_error("Span is too small!"));
	for (unsigned int i = 0; i < N; i += 1)
		if (values[i] > max)
			max = values[i];
	for (unsigned int i = 0; i < N; i += 1)
		if (values[i] < min)
			min = values[i];
	result = max - min;
	return (result);
}
